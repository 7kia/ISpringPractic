#include "stdafx.h"
#include "GlobalFunctions.h"
#include "ShapeCompositorModel.h"


CShapeCompositorModel::CShapeCompositorModel()
	: m_textureStorage(CanvasNamespace::MAX_PICTURE_SIZE)
	, m_canvasModel(CanvasNamespace::CANVAS_SIZE)
{
}

D2D1_RECT_F CShapeCompositorModel::GetCanvasRect() const
{
	return m_canvasModel.GetRect();
}

void CShapeCompositorModel::SetRenderTargetForModelComponents(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_imageFactory.SetRenderTarget(pRenderTarget);
}


bool CShapeCompositorModel::SaveAsDocument()
{
	bool isSave = m_document.OnFileSaveAs(
		m_canvasModel.GetShapes(),
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
		m_canvasModel.GetShapes(),
		m_textureStorage
	);
	if (isSave)
	{
		m_history.DoSave();
	}
	return isSave;
}

bool CShapeCompositorModel::OpenDocument()
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
		m_canvasModel.SetShapes(readData.shapeData);
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
			ResetModel();
			m_document.RecreateTempFolder();
		}
	}
	return false;
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
	m_document.DeletePictures(m_textureStorage.GetDeletable());
	m_textureStorage.Clear();

	m_history.Clear();

	m_resetSelectedShape();

	m_canvasModel.Clear();
}

IShapeCollection & CShapeCompositorModel::GetShapeCollection()
{
	return m_canvasModel.GetShapeCollection();
}

void CShapeCompositorModel::DeleteShape(size_t shapeIndex)
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CDeleteShapeCanvasCommand>(
			m_canvasModel.GetShapeCollection(),
			shapeIndex,
			m_textureStorage
		)
	);
		
}


void CShapeCompositorModel::CreateShape(ShapeType type)
{
	if(type != ShapeType::Picture)
	{
		m_history.AddAndExecuteCommand(
			std::make_shared<CAddShapeCanvasCommand>(
				m_canvasModel.GetShapeCollection(),
				std::make_shared<CShapeModel>(
					type,
					Vec2f(float(CanvasNamespace::CANVAS_SIZE.width) / 2.f, float(CanvasNamespace::CANVAS_SIZE.height) / 2.f)
				),
				m_textureStorage
			)
		);
	}
	else 
	{
		auto picturePath = m_document.LoadTexture();
		if (!picturePath.empty())
		{
			LoadPicture(picturePath);
		}
	}
}

void CShapeCompositorModel::LoadPicture(const boost::filesystem::path & path)
{
	const auto pictureName = path.filename().generic_wstring();

	m_textureStorage.AddTexture(
		pictureName,
		m_imageFactory.CreateTexture(path.generic_wstring())
	);

	const auto canvasSize = m_canvasModel.GetSize();
	CShapeModelPtr pictureModel = std::make_shared<CPictureModel>(
		m_textureStorage.GetTexture(pictureName),
		Vec2f(float(canvasSize.width) / 2.f, float(canvasSize.height) / 2.f),
		m_textureStorage.GetCorrectSize(pictureName)
	);
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_canvasModel.GetShapeCollection(),
			pictureModel,
			m_textureStorage
			)
	);
}


void CShapeCompositorModel::ChangeRect(const CFrame oldFrame, size_t shapeIndex)
{
	CheckIndex(shapeIndex, m_canvasModel.GetShapeCount());
	
	m_history.AddAndExecuteCommand(std::make_shared<CChangeShapeRectCanvasCommand>(
		m_canvasModel.GetShapeProvider(),
		oldFrame,
		shapeIndex
		)
	);
}

signal::Connection CShapeCompositorModel::DoOnCreateView(std::function<void(CShapeModelPtr&, size_t)> const & action)
{
	return m_canvasModel.DoOnCreateView(action);//m_deleteShape.connect(action);
}
