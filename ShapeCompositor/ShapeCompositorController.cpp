#include "stdafx.h"
#include "ShapeCompositorController.h"

CShapeCompositorController::CShapeCompositorController(CShapeCompositorView & view, CShapeCompositorModel & model)
	: m_view(view)
	, m_model(model)
{
	m_view.SetBoundingRect(m_model.GetCanvasRect());

	SetHistoryManipulator(&model);
	SetDataForSave(&model);
	SetDataForOpen(&model);

	CreateConnectionsForView();
}

void CShapeCompositorController::SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator)
{
	m_pHystoryManipulator = pHystoryManipulator;
	ConnectSignalsForHistory();
}

void CShapeCompositorController::SetDataForSave(IDataForSave * pDataForSave)
{
	m_pDataForSave = pDataForSave;
}

void CShapeCompositorController::SetDataForOpen(IDataForOpen * pDataForOpen)
{
	m_pDataForOpen = pDataForOpen;
}

void CShapeCompositorController::ConnectSignalsForHistory()
{
	m_connections += m_view.DoOnUndoCommand(boost::bind(&IHistoryManipulator::UndoCommand, &m_model));
	m_connections += m_view.DoOnRedoCommand(boost::bind(&IHistoryManipulator::RedoCommand, &m_model));
}

void CShapeCompositorController::CreateConnectionsForView()
{
	m_connections += m_view.DoOnSaveAsDocument(boost::bind(&CShapeCompositorController::SaveAsDocument, *this));
	m_connections += m_view.DoOnSaveDocument(boost::bind(&CShapeCompositorController::SaveDocument, *this));
	m_connections += m_view.DoOnOpenDocument(boost::bind(&CShapeCompositorController::OpenDocument, *this, _1));
	m_connections += m_view.DoOnNewDocument(boost::bind(&CShapeCompositorController::NewDocument, *this));
	
	m_connections += m_view.DoOnGetCanvasView(boost::bind(&CShapeCompositorModel::GetCanvasBorder, &m_model));
	m_connections += m_view.DoOnGetCanvasShapes(boost::bind(&IShapeCollection::GetShapes, &m_model.GetShapeCollection()));


	m_connections += m_view.DoOnSetRenderTargetForImageFactory(
		boost::bind(&CShapeCompositorModel::SetRenderTargetForImageFactory, &m_model, _1)
	);

	m_connections += m_view.DoOnCreatePicture(boost::bind(&CShapeCompositorController::CreatePicture, *this, _1));
	m_connections += m_view.DoOnDeleteShapeCommand(boost::bind(&CShapeCompositorModel::DeleteShape, &m_model, _1));
	m_connections += m_view.DoOnChangeRectCommand(boost::bind(&CShapeCompositorModel::ChangeRect, &m_model, _1, _2));
	m_connections += m_view.DoOnCreateShapeCommand(boost::bind(&CShapeCompositorModel::CreateShape, &m_model, _1, _2));

}

void CShapeCompositorController::ResetShapeCompositor()
{
	auto & textureStorage = m_pDataForSave->GetTextureStorage();
	m_document.DeletePictures(textureStorage.GetDeletable());
	textureStorage.Clear();

	m_pHystoryManipulator->ClearHistory();

	m_view.ResetSelectedShape();

	m_pDataForSave->GetShapeCollection().Clear();
}

bool CShapeCompositorController::SaveAsDocument()
{
	bool isSave = m_document.OnFileSaveAs(
		m_pDataForSave->GetShapeCollection().GetShapes(),
		m_pDataForSave->GetTextureStorage()
	);
	if (isSave)
	{
		m_pHystoryManipulator->DoSave();
	}
	return isSave;
}

bool CShapeCompositorController::SaveDocument()
{
	bool isSave = m_document.OnFileSave(
		m_pDataForSave->GetShapeCollection().GetShapes(),
		m_pDataForSave->GetTextureStorage()
	);
	if (isSave)
	{
		m_pHystoryManipulator->DoSave();
	}
	return isSave;
}

bool CShapeCompositorController::OpenDocument(CSelectedShape & selectedShape)
{
	if (SaveChangeDocument() != IDCANCEL)
	{
		return m_document.OnFileOpen(
			CMyDocument::DataForAlteration
			(
				m_pDataForSave,
				m_pDataForOpen,
				m_pHystoryManipulator,
				selectedShape
			)
		);
	}
	return false;
}

bool CShapeCompositorController::NewDocument()
{
	if (SaveChangeDocument() != IDCANCEL)
	{
		if (!(m_pHystoryManipulator->IsSave() && m_document.IsNewDocument()))
		{
			ResetShapeCompositor();
			m_document.RecreateTempFolder();
		}
	}
	return false;
}

void CShapeCompositorController::CreatePicture(CSelectedShape & selectedShape)
{
	auto picturePath = m_document.LoadTexture();
	if (picturePath != L"no")
	{
		m_model.LoadPicture(picturePath, selectedShape);
	}
}

int CShapeCompositorController::SaveChangeDocument()
{
	int result = IDNO;
	if (!m_pHystoryManipulator->IsSave())
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
