#pragma once

#include "View/ShapeView.h"
#include "ConnectionsStorage.h"

class CShapePresenter
{
public:
	CShapePresenter(CShapeModelPtr & pModel);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// NameInterface

	//--------------------------------------------

	//void			Set();
	//void			Get();
private:
	void ConnectSignalsForView();
	void ConnectSignalsForModel();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeView * m_pView = nullptr;
	CShapeModel * m_pModel = nullptr;

	ScopedConnectionsStorage m_connections;
};