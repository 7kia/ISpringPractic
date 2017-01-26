#include "stdafx.h"
#include "CircleShape.h"

CCircleShape::CCircleShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(position, SSize(size.width / 2.f, size.height / 2.f), fillColor, outlineColor)
{
}

void CCircleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}
