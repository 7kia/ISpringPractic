#include "stdafx.h"
#include "ShapeCompositorPresenter.h"

CShapeCompositorPresenter::CShapeCompositorPresenter(CShapeCompositorView * view)
	: m_pView(view)
{
}

void CShapeCompositorPresenter::SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator)
{
	m_pHystoryManipulator = pHystoryManipulator;
	ConnectSignalsForHistory();
}

void CShapeCompositorPresenter::SetShapeManipulator(IShapeManipulator * pShapeManipulator)
{
	m_pShapeManipulator = pShapeManipulator;
	ConnectSignalsForShapeManipulator();
}

void CShapeCompositorPresenter::SetDocumentManipulator(IDocumentManipulator * pDocumentManipulator)
{
	m_pDocumentManipulator = pDocumentManipulator;
	ConnectSignalsForDocumentManipulator();
}

void CShapeCompositorPresenter::SetDataForDraw(IDataForDraw * pDataForDraw)
{
	m_pDataForDraw = pDataForDraw;
	ConnectSignalsForDataForDraw();
}

void CShapeCompositorPresenter::SetHaveRenderTarget(IHaveRenderTarget * pHaveRenderTarget)
{
	m_pHaveRenderTarget = pHaveRenderTarget;
	ConnectSignalsForHaveRenderTarget();
}

void CShapeCompositorPresenter::SetModelReseter(IModelReseter * pModelReseter)
{
	m_pModelReseter = pModelReseter;

	ConnectSignalsForModelReseter();
}

void CShapeCompositorPresenter::ConnectSignalsForHistory()
{
	m_connections += m_pView->DoOnUndoCommand(boost::bind(&IHistoryManipulator::UndoCommand, m_pHystoryManipulator));
	m_connections += m_pView->DoOnRedoCommand(boost::bind(&IHistoryManipulator::RedoCommand, m_pHystoryManipulator));
}

void CShapeCompositorPresenter::ConnectSignalsForDocumentManipulator()
{	
	m_connections += m_pView->DoOnSaveAsDocument(boost::bind(&IDocumentManipulator::SaveAsDocument, m_pDocumentManipulator));
	m_connections += m_pView->DoOnSaveDocument(boost::bind(&IDocumentManipulator::SaveDocument, m_pDocumentManipulator));
	m_connections += m_pView->DoOnOpenDocument(boost::bind(&IDocumentManipulator::OpenDocument, m_pDocumentManipulator, _1));
	m_connections += m_pView->DoOnNewDocument(boost::bind(&IDocumentManipulator::NewDocument, m_pDocumentManipulator));
}

void CShapeCompositorPresenter::ConnectSignalsForShapeManipulator()
{
	m_connections += m_pView->DoOnDeleteShapeCommand(boost::bind(&IShapeManipulator::DeleteShape, m_pShapeManipulator, _1));
	m_connections += m_pView->DoOnChangeRectCommand(boost::bind(&IShapeManipulator::ChangeRect, m_pShapeManipulator, _1, _2));
	m_connections += m_pView->DoOnCreateShapeCommand(boost::bind(&IShapeManipulator::CreateShape, m_pShapeManipulator , _1, _2));
}

void CShapeCompositorPresenter::ConnectSignalsForDataForDraw()
{	
	// TODO : see need rewrite shape on MVC or MVP
	m_connections += m_pView->DoOnGetCanvasView(boost::bind(&IDataForDraw::GetCanvasBorder, m_pDataForDraw));
	m_connections += m_pView->DoOnGetCanvasShapes(boost::bind(&IDataForDraw::GetCanvasShapes, m_pDataForDraw));
}

void CShapeCompositorPresenter::ConnectSignalsForHaveRenderTarget()
{
	m_connections += m_pView->DoOnSetRenderTargetForModel(
		boost::bind(&IHaveRenderTarget::SetRenderTargetForModelComponents, m_pHaveRenderTarget, _1)
	);
}

void CShapeCompositorPresenter::ConnectSignalsForModelReseter()
{
	// TODO : think need interface for ResetSelectedShape()
	m_connections += m_pModelReseter->DoOnResetSelectedShape(boost::bind(&CShapeCompositorView::ResetSelectedShape, m_pView));
}
