#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape()
	: CObservable<SPresenterData>()
{
}

void CSelectShape::SetShape(CShapePresenterPtr shape)
{

	if (shape != m_selectPresenter.lock())
	{
		if (!m_selectPresenter.expired())
		{
			RemoveObserver(*m_selectPresenter.lock().get());
		}

		RegisterObserver(*shape.get());
	}

	m_selectPresenter = shape;
	m_frameData = shape->GetChangedData();

}

CShapePresenterPtr CSelectShape::GetShape() const
{
	return CShapePresenterPtr(m_selectPresenter);
}

SPresenterData CSelectShape::GetChangedData() const
{ 
	return m_frameData;
}
