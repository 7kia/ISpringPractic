#include "stdafx.h"
#include "ShapePresenter.h"

CShapePresenter::CShapePresenter(const Vec2f position, const SSize size)
	: m_position(position)
	, m_size(size)
{
}

CShapePresenter::~CShapePresenter()
{
}

void CShapePresenter::CheckPointIntersection(const Vec2f point)
{
	if (IsPointIntersection(point))
	{
		NotifyObservers();// TODO : check need it there
	}
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

	NotifyObservers();
}
