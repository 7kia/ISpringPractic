#include "stdafx.h"
#include "EllipseShapeData.h"

CEllipseDataShape::CEllipseDataShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShapeData(position, SSize(size.width / 2.f, size.height / 2.f), fillColor, outlineColor)
{
}

void CEllipseDataShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}