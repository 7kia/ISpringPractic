#include "stdafx.h"
#include "ShapeCompositorModel.h"


CShapeCompositorModel::CShapeCompositorModel()
	: m_textureStorage(CanvasNamespace::MAX_PICTURE_SIZE)
	, m_canvas(CanvasNamespace::CANVAS_SIZE)
{
	m_canvasBorder = m_shapeFactory.CreateShape(
		SShapeData(
			ShapeType::Rectangle,
			Vec2f(
				CanvasNamespace::CANVAS_SIZE.width / 2.f,
				CanvasNamespace::CANVAS_SIZE.height / 2.f
			),
			CanvasNamespace::CANVAS_SIZE,
			NOT_COLOR,
			BLACK_COLOR,
			3.f
		)
	);
}


D2D1_RECT_F CShapeCompositorModel::GetCanvasRect() const
{
	return m_canvas.GetRect();
}

CShapePtr CShapeCompositorModel::GetCanvasBorder() const
{
	return m_canvasBorder;
}

bool CShapeCompositorModel::SaveAsDocument()
{
	bool isSave = m_document.OnFileSaveAs(
		m_canvas.GetShapes(),
		m_textureStorage
	);
	if (isSave)
	{
		m_history.DoSave();
	}
	return isSave;
}

bool CShapeCompositorModel::SaveDocument()
{
	bool isSave = m_document.OnFileSave(
		m_canvas.GetShapes(),
		m_textureStorage
	);
	if (isSave)
	{
		m_history.DoSave();
	}
	return isSave;
}

bool CShapeCompositorModel::OpenDocument(CSelectedShape & selectedShape)
{
	if (SaveChangeDocument() != IDCANCEL)
	{
		auto readData = m_document.OnFileOpen(	
			this,
			m_textureStorage.GetDeletable(),
			CXMLReader::DataForCreation(
				m_shapeFactory,
				m_imageFactory
			)
		);
		m_canvas.SetShapes(readData.shapeData);
		m_textureStorage = readData.textureStorage;
		return true;
	}
	return false;
}

bool CShapeCompositorModel::NewDocument()
{
	if (SaveChangeDocument() != IDCANCEL)
	{
		if (!(m_history.IsSave() && m_document.IsNewDocument()))
		{
			ResetShapeCompositor();
			m_document.RecreateTempFolder();
		}
	}
	return false;
}

void CShapeCompositorModel::ResetShapeCompositor()
{
	m_document.DeletePictures(m_textureStorage.GetDeletable());
	m_textureStorage.Clear();

	m_history.Clear();

	m_resetSelectedShape();

	m_canvas.Clear();
}

int CShapeCompositorModel::SaveChangeDocument()
{
	int result = IDNO;
	if (!m_history.IsSave())
	{
		result = AfxMessageBox(L"Сохранить изменения?", MB_YESNOCANCEL);

		if (m_document.IsNewDocument())
		{
			if (result == IDYES)
			{
				SaveAsDocument();
			}
		}
		else
		{
			if (result == IDYES)
			{
				SaveDocument();
			}
		}
	}

	return result;
}


void CShapeCompositorModel::LoadPicture(const boost::filesystem::path & path, CSelectedShape & selectedShape)
{
	const auto pictureName = path.filename().generic_wstring();

	m_textureStorage.AddTexture(
		pictureName,
		m_imageFactory.CreateTexture(path.generic_wstring())
	);

	const auto canvasSize = m_canvas.GetSize();
	m_history.AddAndExecuteCommand(std::make_shared<CAddPictureCommand>(
		m_canvas.GetShapeCollection(),
		SPictureData(
			m_textureStorage.GetTexture(pictureName),
			Vec2f(float(canvasSize.width) / 2.f, float(canvasSize.height) / 2.f),
			m_textureStorage.GetCorrectSize(pictureName)
		),
		m_textureStorage,
		selectedShape
		)
	);
}


void CShapeCompositorModel::SetRenderTargetForImageFactory(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_imageFactory.SetRenderTarget(pRenderTarget);
}

signal::Connection CShapeCompositorModel::DoOnResetSelectedShape(std::function<void()> const & action)
{
	return m_resetSelectedShape.connect(action);
}

void CShapeCompositorModel::UndoCommand()
{
	m_history.Undo();
}

void CShapeCompositorModel::RedoCommand()
{
	m_history.Redo();
}

void CShapeCompositorModel::ClearHistory()
{
	m_history.Clear();
}

bool CShapeCompositorModel::IsSave() const
{
	return m_history.IsSave();
}

void CShapeCompositorModel::DoSave()
{
	m_history.DoSave();
}

void CShapeCompositorModel::ResetModel()
{
	m_textureStorage.Clear();
	m_history.Clear();
	m_resetSelectedShape();
	m_canvas.Clear();
}

IShapeCollection & CShapeCompositorModel::GetShapeCollection()
{
	return m_canvas.GetShapeCollection();
}

void CShapeCompositorModel::DeleteShape(CSelectedShape & selectedShape)
{
	if (selectedShape.GetShape()->GetType() == ShapeType::Picture)
	{
		m_history.AddAndExecuteCommand(
			std::make_shared<CDeletePictureCommand>(
				m_canvas.GetShapeCollection()
				, selectedShape
				, m_textureStorage
				)
		);
	}
	else
	{
		m_history.AddAndExecuteCommand(
			std::make_shared<CDeleteShapeCanvasCommand>(
				m_canvas.GetShapeCollection()
				, selectedShape
				, m_shapeFactory
				)
		);	
	}	
}

void CShapeCompositorModel::CreateShape(ShapeType type, CSelectedShape & selectedShape)
{
	if(type != ShapeType::Picture)
	{
		m_history.AddAndExecuteCommand(
			std::make_shared<CAddShapeCanvasCommand>(
				m_canvas.GetShapeCollection(),
				type,
				m_shapeFactory,
				selectedShape
			)
		);
	}
	else 
	{
		auto picturePath = m_document.LoadTexture();
		if (!picturePath.empty())
		{
			LoadPicture(picturePath, selectedShape);
		}
	}
}

void CShapeCompositorModel::ChangeRect(const CFrame oldFrame, CSelectedShape & selectedShape)
{
	m_history.AddAndExecuteCommand(std::make_shared<CChangeShapeRectCanvasCommand>(
		m_canvas.GetShapeProvider(),
		oldFrame,
		selectedShape.GetFrame(),
		selectedShape
		)
	);
}
