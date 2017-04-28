#pragma once

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ConnectionsStorage.h"

class IHistoryManipulator;
class IDataForSave;

class CShapeCompositorController
{
public:
	CShapeCompositorController(CShapeCompositorView & view, CShapeCompositorModel & model);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetHistoryManipulator(IHistoryManipulator * pHystoryManipulator);
	void SetDataForSave(IDataForSave * pDataForSave);

private:
	void ConnectSignalsForHistory();

	void CreateConnectionsForView();


	void CreatePicture(CSelectedShape & selectedShape);
	int	CheckSaveDocument();
	// TODO: rename
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeCompositorView & m_view;


	IHistoryManipulator * m_pHystoryManipulator = nullptr;
	IDataForSave * m_pDataForSave = nullptr;
	CShapeCompositorModel & m_model;
	CMyDocument m_document;

	ScopedConnectionsStorage m_connections;
};
