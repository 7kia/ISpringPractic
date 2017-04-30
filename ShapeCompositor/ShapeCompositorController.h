#pragma once

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ConnectionsStorage.h"


class CShapeCompositorController
{
public:
	CShapeCompositorController(CShapeCompositorView & view, CShapeCompositorModel & model);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator);
	void SetDataForSave(IDataForSave * pDataForSave);
	void SetDataForOpen(IDataForOpen * pDataForOpen);
	void SetDocumentManipulator(IDocumentManipulator * pDocumentManipulator);
private:
	void ConnectSignalsForHistory();
	void ConnectSignalsForDocumentManipulator();

	void CreateConnectionsForView();

	// TODO: rename
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeCompositorView & m_view;

	IHistoryManipulator * m_pHystoryManipulator = nullptr;
	IDataForSave * m_pDataForSave = nullptr;
	IDataForOpen * m_pDataForOpen = nullptr;
	IDocumentManipulator * m_pDocumentManipulator = nullptr;
	CShapeCompositorModel & m_model;

	ScopedConnectionsStorage m_connections;
};
