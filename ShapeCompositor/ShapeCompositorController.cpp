#include "stdafx.h"
#include "ShapeCompositorController.h"

CShapeCompositorController::CShapeCompositorController(CShapeCompositorView & view, CShapeCompositorModel & model)
	: m_view(view)
	, m_model(model)
{
	m_view.SetBoundingRect(m_model.GetCanvasRect());

	SetHistoryManipulator(&model);
	SetDocumentManipulator(&model);

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

void CShapeCompositorController::SetDocumentManipulator(IDocumentManipulator * pDocumentManipulator)
{
	m_pDocumentManipulator = pDocumentManipulator;
	ConnectSignalsForDocumentManipulator();
}

void CShapeCompositorController::ConnectSignalsForHistory()
{
	m_connections += m_view.DoOnUndoCommand(boost::bind(&IHistoryManipulator::UndoCommand, m_pHystoryManipulator));
	m_connections += m_view.DoOnRedoCommand(boost::bind(&IHistoryManipulator::RedoCommand, m_pHystoryManipulator));
}

void CShapeCompositorController::ConnectSignalsForDocumentManipulator()
{	
	m_connections += m_view.DoOnSaveAsDocument(boost::bind(&IDocumentManipulator::SaveAsDocument, m_pDocumentManipulator));
	m_connections += m_view.DoOnSaveDocument(boost::bind(&IDocumentManipulator::SaveDocument, m_pDocumentManipulator));
	m_connections += m_view.DoOnOpenDocument(boost::bind(&IDocumentManipulator::OpenDocument, m_pDocumentManipulator, _1));
	m_connections += m_view.DoOnNewDocument(boost::bind(&IDocumentManipulator::NewDocument, m_pDocumentManipulator));
}

void CShapeCompositorController::CreateConnectionsForView()
{
	m_connections += m_model.DoOnResetSelectedShape(boost::bind(&CShapeCompositorView::ResetSelectedShape, &m_view));

	// TODO : see need rewrite shape on MVC or MVP
	m_connections += m_view.DoOnGetCanvasView(boost::bind(&CShapeCompositorModel::GetCanvasBorder, &m_model));
	m_connections += m_view.DoOnGetCanvasShapes(boost::bind(&IShapeCollection::GetShapes, &m_model.GetShapeCollection()));


	m_connections += m_view.DoOnSetRenderTargetForImageFactory(
		boost::bind(&CShapeCompositorModel::SetRenderTargetForImageFactory, &m_model, _1)
	);

	m_connections += m_view.DoOnDeleteShapeCommand(boost::bind(&CShapeCompositorModel::DeleteShape, &m_model, _1));
	m_connections += m_view.DoOnChangeRectCommand(boost::bind(&CShapeCompositorModel::ChangeRect, &m_model, _1, _2));
	m_connections += m_view.DoOnCreateShapeCommand(boost::bind(&CShapeCompositorModel::CreateShape, &m_model, _1, _2));

}
