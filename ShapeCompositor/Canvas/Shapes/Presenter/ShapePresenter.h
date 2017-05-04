#pragma once

#include "View/ShapeView.h"

class CShapePresenter
{
public:
	CShapePresenter(CShapeView * pView, CShapeModelPtr & pModel);
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
	CShapeModelPtr m_pModel;
};