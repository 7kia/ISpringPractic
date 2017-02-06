#include "stdafx.h"
#include "EllipsePresenter.h"

CEllipsePresenter::CEllipsePresenter(const Vec2f position, const SSize size)
	: CShapePresenter(position, size)	
{
}

bool CEllipsePresenter::IsPointIntersection(const Vec2f point) const
{
	const float a = m_size.width * m_size.width;
	const float b = m_size.height * m_size.height;
	const float x = powf((point.x - m_position.x), 2.f);
	const float y = powf((point.y - m_position.y), 2.f);

	return ((b * x) + (a * y)) <= (a * b);
}
