#include "stdafx.h"
#include "ShapeCompositorModel.h"

namespace
{
	static const SSize CANVAS_SIZE = SSize(640.f, 480.f);
	static const float SCALE_FACTOR = 0.8f;
	static const SSize MAX_SIZE = SSize(CANVAS_SIZE.width * SCALE_FACTOR, CANVAS_SIZE.height * SCALE_FACTOR);
}

CShapeCompositorModel::CShapeCompositorModel()
	: m_textureStorage(MAX_SIZE)
	, m_canvas(CANVAS_SIZE)
{
	m_canvasBorder = m_shapeFactory.CreateShape(
		SShapeData(
			ShapeType::Rectangle,
			Vec2f(CANVAS_SIZE.width / 2.f, CANVAS_SIZE.height / 2.f),
			CANVAS_SIZE,
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
		return m_document.OnFileOpen(
			CMyDocument::DataForAlteration
			(
				m_canvas.GetShapeCollection(),
				m_shapeFactory,
				&m_history,
				selectedShape,
				m_textureStorage,
				m_imageFactory
			)
		);
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

void CShapeCompositorModel::CreatePicture(CSelectedShape & selectedShape)
{
	auto picturePath = m_document.LoadTexture();
	if (picturePath != L"no")
	{
		LoadPicture(picturePath, selectedShape);
	}
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
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_canvas.GetShapeCollection()
			, type
			, m_shapeFactory
			, selectedShape
			)
	);
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
