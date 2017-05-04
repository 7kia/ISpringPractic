#include "stdafx.h"
#include "ShapePresenter.h"
#include "../ShapeViewFactory.h"

CShapePresenter::CShapePresenter(CShapeModelPtr & pModel)
	: m_pModel(pModel)
{
	m_pView = CShapeViewFactory::CreateShape(pModel);
	ConnectSignalsForView();
	ConnectSignalsForModel();
}

void CShapePresenter::ConnectSignalsForView()
{
}

void CShapePresenter::ConnectSignalsForModel()
{
}
