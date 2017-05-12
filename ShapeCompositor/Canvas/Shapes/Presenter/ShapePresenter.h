#pragma once

#include "../View/ShapeView.h"
#include "ConnectionsStorage.h"

class CShapePresenter
{
public:
	CShapePresenter(CShapeModelPtr & pModel);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetShapeView(CShapeView * pView);
private:
	void ConnectSignalsForModel();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeView * m_pView = nullptr;
	CShapeModel * m_pModel = nullptr;

	ScopedConnectionsStorage m_connections;
};