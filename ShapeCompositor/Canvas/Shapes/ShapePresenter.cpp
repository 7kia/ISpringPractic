#include "stdafx.h"
#include "ShapePresenter.h"

CShapePresenter::CShapePresenter(const Vec2f position, const SSize size)
	: m_position(position)
	, m_size(size)
{
}

void CShapePresenter::CheckPointIntersection(const Vec2f point)
{
	if (IsPointIntersection(point))
	{
		NotifyObservers();
	}
}