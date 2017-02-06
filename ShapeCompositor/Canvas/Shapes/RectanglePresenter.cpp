#include "stdafx.h"
#include "RectanglePresenter.h"

CRectanglePresenter::CRectanglePresenter(const Vec2f position, const SSize size)
	: CShapePresenter(position, size)
{
}

bool CRectanglePresenter::IsPointIntersection(const Vec2f point) const
{
	return IsBetween(point.x, m_position.x - m_size.width / 2.f, m_position.x + m_size.width / 2.f)
		&& IsBetween(point.y, m_position.y - m_size.height / 2.f, m_position.y + m_size.height / 2.f);
}
