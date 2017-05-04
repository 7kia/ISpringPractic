#pragma once

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ConnectionsStorage.h"


class CShapeCompositorPresenter
{
public:
	CShapeCompositorPresenter(IViewSignaller * pViewSignaller);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator);
	void SetShapeManipulator(IShapeManipulator * pShapeManipulator);
	void SetDocumentManipulator(IDocumentManipulator * pDocumentManipulator);
	void SetHaveRenderTarget(IHaveRenderTarget * pHaveRenderTarget);
	void SetModelReseter(IModelReseter * pModelReseter, IViewReseter * pViewReseter);
private:
	void ConnectSignalsForHistory();
	void ConnectSignalsForDocumentManipulator();
	void ConnectSignalsForShapeManipulator();
	void ConnectSignalsForHaveRenderTarget();
	void ConnectSignalsForModelReseter();
	void ConnectSignalsForView();
	// TODO: rename
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	IViewSignaller * m_pViewSignaller = nullptr;
	IViewReseter * m_pViewReseter = nullptr;
	IHistoryManipulator * m_pHystoryManipulator = nullptr;
	IDocumentManipulator * m_pDocumentManipulator = nullptr;
	IShapeManipulator * m_pShapeManipulator = nullptr;
	IHaveRenderTarget * m_pHaveRenderTarget = nullptr;
	IModelReseter * m_pModelReseter = nullptr;
	ScopedConnectionsStorage m_connections;
};
