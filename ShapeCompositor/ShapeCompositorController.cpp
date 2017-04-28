#include "stdafx.h"
#include "ShapeCompositorController.h"

CShapeCompositorController::CShapeCompositorController(CShapeCompositorView & view, CShapeCompositorModel & model)
	: m_view(view)
	, m_model(model)
{
	m_view.SetBoundingRect(m_model.GetCanvasRect());
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

void CShapeCompositorController::ConnectSignalsForHistory()
{
	m_connections += m_view.DoOnUndoCommand(boost::bind(&IHistoryManipulator::UndoCommand, *this));
	m_connections += m_view.DoOnRedoCommand(boost::bind(&IHistoryManipulator::RedoCommand, *this));
}

void CShapeCompositorController::CreateConnectionsForView()
{
	m_connections += m_view.DoOnGetCanvasView(boost::bind(&CShapeCompositorModel::GetCanvasBorder, &m_model));
	m_connections += m_view.DoOnGetCanvasShapes(boost::bind(&CShapeCompositorModel::GetCanvasShapes, &m_model));
	m_connections += m_view.DoOnCreatePicture(boost::bind(&CShapeCompositorController::CreatePicture, *this, _1));


	m_connections += m_view.DoOnCreateShapeCommand(boost::bind(&CShapeCompositorModel::CreateShape, *this, _1, _2));
	m_connections += m_view.DoOnSetRenderTargetForImageFactory(boost::bind(&CShapeCompositorModel::SetRenderTargetForImageFactory, *this, _1));

}

void CShapeCompositorController::CreatePicture(CSelectedShape & selectedShape)
{
	auto picturePath = m_document.LoadTexture();
	if (picturePath != L"no")
	{
		m_model.LoadPicture(picturePath, selectedShape);
	}
}

int CShapeCompositorController::CheckSaveDocument()
{
	int result = IDNO;
	if (!m_pHystoryManipulator->IsSave())
	{
		result = AfxMessageBox(L"Сохранить изменения?", MB_YESNOCANCEL);

		if (m_document.IsNewDocument())
		{
			if (result == IDYES)
			{
				if (m_document.OnFileSaveAs(m_pDataForSave->GetCanvasShapes(), m_pDataForSave->GetTextureStorage()))
				{
					m_pHystoryManipulator->DoSave();
				}
			}
		}
		else
		{
			if (result == IDYES)
			{
				if (m_document.OnFileSave(m_pDataForSave->GetCanvasShapes(), m_pDataForSave->GetTextureStorage()))
				{
					m_pHystoryManipulator->DoSave();
				}
			}
		}
	}

	return result;
}
