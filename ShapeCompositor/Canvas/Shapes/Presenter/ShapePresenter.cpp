#include "stdafx.h"
#include "ShapePresenter.h"
#include "../ShapeViewFactory.h"

CShapePresenter::CShapePresenter(CShapeModelPtr & pModel)
	: m_pModel(pModel.get())
{
}

void CShapePresenter::SetShapeView(CShapeView * pView)
{
	m_pView = pView;
	ConnectSignalsForModel();
}

void CShapePresenter::ConnectSignalsForModel()
{
	m_connections += m_pModel->DoOnRectChanged(boost::bind(&CShapeView::Update, m_pView, _1));
}
