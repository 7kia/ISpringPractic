#include "stdafx.h"
#include "EllipseShape.h"

CEllipseShape::CEllipseShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(position, SSize(size.width / 2.f, size.height / 2.f), fillColor, outlineColor)
{
}

void CEllipseShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

bool CEllipseShape::IsPointIntersection(const Vec2f point) const
{	
	const float a = m_size.width * m_size.width;
	const float b = m_size.height * m_size.height;
	const float x = point.x * point.x;
	const float y = point.y * point.y;

	return ((b * x) + (a * y)) <= (a * b);
}
