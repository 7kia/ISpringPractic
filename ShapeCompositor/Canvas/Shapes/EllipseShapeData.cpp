#include "stdafx.h"
#include "EllipseShapeData.h"

CEllipseDataShape::CEllipseDataShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShapeData(position, SSize(size.width, size.height), fillColor, outlineColor)
{
}

void CEllipseDataShape::Accept(IRenderShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}