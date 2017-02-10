#include "stdafx.h"
#include "EllipsePresenter.h"

CEllipsePresenter::CEllipsePresenter(const Vec2f position, const SSize size)
	: CShapePresenter(position, size)	
{
}

bool CEllipsePresenter::IsPointIntersection(const Vec2f point) const
{
	const float a = powf(m_size.width / 2.f, 2.f);
	const float b = powf(m_size.height / 2.f, 2.f);
	const float x = powf((point.x - m_position.x), 2.f);
	const float y = powf((point.y - m_position.y), 2.f);

	return ((b * x) + (a * y)) <= (a * b);
}
