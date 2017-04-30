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
private:
	void ConnectSignalsForHistory();

	void CreateConnectionsForView();

	void ResetShapeCompositor();
	// TODO : see need interface
	bool SaveAsDocument();
	bool SaveDocument();
	bool OpenDocument(CSelectedShape & selectedShape);
	bool NewDocument();
	//

	void CreatePicture(CSelectedShape & selectedShape);
	int	SaveChangeDocument();
	// TODO: rename
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeCompositorView & m_view;


	IHistoryManipulator * m_pHystoryManipulator = nullptr;
	IDataForSave * m_pDataForSave = nullptr;
	IDataForOpen * m_pDataForOpen = nullptr;
	CShapeCompositorModel & m_model;
	CMyDocument m_document;

	ScopedConnectionsStorage m_connections;
};
