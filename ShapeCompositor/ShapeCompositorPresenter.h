#pragma once

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ConnectionsStorage.h"


class CShapeCompositorPresenter
{
public:
	CShapeCompositorPresenter(CShapeCompositorView * view);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator);
	void SetShapeManipulator(IShapeManipulator * pShapeManipulator);
	void SetDocumentManipulator(IDocumentManipulator * pDocumentManipulator);
	void SetDataForDraw(IDataForDraw * pDataForDraw);
	void SetHaveRenderTarget(IHaveRenderTarget * pHaveRenderTarget);
	void SetModelReseter(IModelReseter * pModelReseter);
private:
	void ConnectSignalsForHistory();
	void ConnectSignalsForDocumentManipulator();
	void ConnectSignalsForShapeManipulator();
	void ConnectSignalsForDataForDraw();
	void ConnectSignalsForHaveRenderTarget();
	void ConnectSignalsForModelReseter();

	// TODO: rename
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeCompositorView * m_pView = nullptr;

	IHistoryManipulator * m_pHystoryManipulator = nullptr;
	IDocumentManipulator * m_pDocumentManipulator = nullptr;
	IShapeManipulator * m_pShapeManipulator = nullptr;
	IDataForDraw * m_pDataForDraw = nullptr;
	IHaveRenderTarget * m_pHaveRenderTarget = nullptr;
	IModelReseter * m_pModelReseter = nullptr;
	ScopedConnectionsStorage m_connections;
};
