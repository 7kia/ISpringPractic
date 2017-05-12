#include "stdafx.h"
#include "GlobalFunctions.h"
#include "ShapeCompositorModel.h"


CShapeCompositorModel::CShapeCompositorModel()
	: m_textureStorage(CanvasNamespace::MAX_PICTURE_SIZE)
	, m_domainModel(CanvasNamespace::CANVAS_SIZE)
{
}

D2D1_RECT_F CShapeCompositorModel::GetCanvasRect() const
{
	return m_domainModel.GetRect();
}

void CShapeCompositorModel::SetRenderTargetForModelComponents(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_imageFactory.SetRenderTarget(pRenderTarget);
}


bool CShapeCompositorModel::SaveAsDocument()
{
	bool isSave = m_document.OnFileSaveAs(
		m_domainModel.GetShapes(),
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
		m_domainModel.GetShapes(),
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
			GetModelReseter(),
			m_textureStorage.GetDeletable(),
			CXMLReader::DataForCreation(
				m_shapeFactory,
				m_imageFactory
			)
		);
		m_domainModel.SetShapes(readData.shapeData);
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


signal::Connection CShapeCompositorModel::DoOnResetView(std::function<void()> const & action)
{
	return m_resetView.connect(action);
}

IModelReseter & CShapeCompositorModel::GetModelReseter()
{
	return *this;
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

	m_domainModel.Clear();
	m_resetView();
}


void CShapeCompositorModel::DeleteShape(size_t shapeIndex)
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CDeleteShapeCanvasCommand>(
			m_domainModel.GetShapeCollection(),
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
				m_domainModel.GetShapeCollection(),
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

	const auto canvasSize = m_domainModel.GetSize();
	CShapeModelPtr pictureModel = std::make_shared<CPictureModel>(
		m_textureStorage.GetTexture(pictureName),
		Vec2f(float(canvasSize.width) / 2.f, float(canvasSize.height) / 2.f),
		m_textureStorage.GetCorrectSize(pictureName)
	);
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_domainModel.GetShapeCollection(),
			pictureModel,
			m_textureStorage
			)
	);
}


void CShapeCompositorModel::ChangeRect(const CFrame oldFrame, const CFrame newFrame, size_t shapeIndex)
{
	CheckIndex(shapeIndex, m_domainModel.GetShapeCount() - 1);
	
	m_history.AddAndExecuteCommand(std::make_shared<CChangeShapeRectCanvasCommand>(
		m_domainModel.GetShapeProvider(),
		oldFrame,
		newFrame,
		shapeIndex
		)
	);
}

signal::Connection CShapeCompositorModel::DoOnCreateView(std::function<void(const CShapeViewPtr&, size_t)> const & action)
{
	return m_domainModel.DoOnCreateView(action);//m_deleteShape.connect(action);
}

signal::Connection CShapeCompositorModel::DoOnDeleteView(std::function<void(size_t)> const & action)
{
	return m_domainModel.DoOnDeleteView(action);//m_deleteShape.connect(action);
}
