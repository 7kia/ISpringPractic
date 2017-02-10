#include "stdafx.h"
#include "ShapePresenter.h"

CShapePresenter::CShapePresenter(const Vec2f position, const SSize size)
	: CObservable<SPresenterData>()// For update view and model
	, IObserver<SPresenterData>()
	, IIsPointIntersection()
	, m_position(position)
	, m_size(size)
{
}

CShapePresenter::~CShapePresenter()
{
}

bool CShapePresenter::CheckPointIntersection(const Vec2f point)
{
	bool result = IsPointIntersection(point);
	if (result)
	{
		NotifyObservers();// TODO : check need it there
	}
	return result;
}

SPresenterData CShapePresenter::GetChangedData() const
{
	SPresenterData info;
	info.position = m_position;
	info.size = m_size;
	return info;
}

void CShapePresenter::Update(const SPresenterData & data)
{
	m_position = data.position;
	m_size = data.size;
}
