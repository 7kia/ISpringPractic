#include "stdafx.h"
#include "RectangleShapeData.h"

CRectangleShapeData::CRectangleShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: CShapeModel(position, size, fillColor, outlineColor)
{
}


void CRectangleShapeData::Accept(IRenderShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}
