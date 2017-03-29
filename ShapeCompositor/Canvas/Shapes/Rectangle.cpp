#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(
		ShapeType::Rectangle
		, position
		, size
		, fillColor
		, outlineColor
	) 
{
}

bool CRectangle::IsPointIntersection(const Vec2f point) const
{
	D2D1_RECT_F ownRect = ::GetFrameRect(*this);
	if (ownRect.left > ownRect.right)
	{
		std::swap(ownRect.left, ownRect.right);
	}
	if (ownRect.top > ownRect.bottom)
	{
		std::swap(ownRect.top, ownRect.bottom);
	}
	return IsBetween(point.x, float(ownRect.left), float(ownRect.right))
		&& IsBetween(point.y, float(ownRect.top), float(ownRect.bottom));
}

ListVertices CRectangle::GetVertices() const
{
	return GetFrameVertices();
}

void CRectangle::Accept(IShapeVisitor & renderer) const
{
	renderer.Visit(*this);
}