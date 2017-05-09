#include "stdafx.h"
#include "ShapeCompositorPresenter.h"

CShapeCompositorPresenter::CShapeCompositorPresenter(IViewSignaller * pViewSignaller)
	: m_pViewSignaller(pViewSignaller)
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


void CShapeCompositorPresenter::SetHaveRenderTarget(IHaveRenderTarget * pHaveRenderTarget)
{
	m_pHaveRenderTarget = pHaveRenderTarget;
	ConnectSignalsForHaveRenderTarget();
}

void CShapeCompositorPresenter::SetModelReseter(IModelReseter * pModelReseter, IViewReseter* pViewReseter)
{
	m_pModelReseter = pModelReseter;
	m_pViewReseter = pViewReseter;
	ConnectSignalsForModelReseter();
}

void CShapeCompositorPresenter::SetShapeViewManipulator(IShapeViewManipulator * pShapeViewCreator)
{
	m_pShapeViewManipulator = pShapeViewCreator;
	ConnectSignalsForShapeViewCreator();
}

void CShapeCompositorPresenter::ConnectSignalsForHistory()
{
	m_connections += m_pViewSignaller->DoOnUndoCommand(boost::bind(&IHistoryManipulator::UndoCommand, m_pHystoryManipulator));
	m_connections += m_pViewSignaller->DoOnRedoCommand(boost::bind(&IHistoryManipulator::RedoCommand, m_pHystoryManipulator));
}

void CShapeCompositorPresenter::ConnectSignalsForDocumentManipulator()
{	
	m_connections += m_pViewSignaller->DoOnSaveAsDocument(boost::bind(&IDocumentManipulator::SaveAsDocument, m_pDocumentManipulator));
	m_connections += m_pViewSignaller->DoOnSaveDocument(boost::bind(&IDocumentManipulator::SaveDocument, m_pDocumentManipulator));
	m_connections += m_pViewSignaller->DoOnOpenDocument(boost::bind(&IDocumentManipulator::OpenDocument, m_pDocumentManipulator));
	m_connections += m_pViewSignaller->DoOnNewDocument(boost::bind(&IDocumentManipulator::NewDocument, m_pDocumentManipulator));
}

void CShapeCompositorPresenter::ConnectSignalsForShapeManipulator()
{
	m_connections += m_pViewSignaller->DoOnDeleteShapeCommand(boost::bind(&IShapeManipulator::DeleteShape, m_pShapeManipulator, _1));
	m_connections += m_pViewSignaller->DoOnChangeRectCommand(boost::bind(&IShapeManipulator::ChangeRect, m_pShapeManipulator, _1, _2, _3));
	m_connections += m_pViewSignaller->DoOnCreateShapeCommand(boost::bind(&IShapeManipulator::CreateShape, m_pShapeManipulator , _1));
}

void CShapeCompositorPresenter::ConnectSignalsForHaveRenderTarget()
{
	m_connections += m_pViewSignaller->DoOnSetRenderTargetForModel(
		boost::bind(&IHaveRenderTarget::SetRenderTargetForModelComponents, m_pHaveRenderTarget, _1)
	);
}

void CShapeCompositorPresenter::ConnectSignalsForModelReseter()
{
	m_connections += m_pModelReseter->DoOnResetSelectedShape(boost::bind(&IViewReseter::ResetSelectedShape, m_pViewReseter));
}

void CShapeCompositorPresenter::ConnectSignalsForView()
{
	//m_connections += m_pViewSignaller->DoOnDeleteShapeCommand(boost::bind(&IViewReseter::ResetSelectedShape, m_pViewReseter));

}

void CShapeCompositorPresenter::ConnectSignalsForShapeViewCreator()
{
	m_connections += m_pShapeManipulator->DoOnDeleteView(boost::bind(&IShapeViewManipulator::DeleteShapeView, m_pShapeViewManipulator, _1));
	m_connections += m_pShapeManipulator->DoOnCreateView(boost::bind(&IShapeViewManipulator::AddShapeView, m_pShapeViewManipulator, _1, _2));


}
