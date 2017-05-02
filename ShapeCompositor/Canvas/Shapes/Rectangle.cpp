#include "stdafx.h"
#include "GlobalFunctions.h"
#include "Rectangle.h"

CRectangle::CRectangle(
	const Vec2f position = Vec2f(),
	const SSize size = DEFAULT_SIZE,
	const Color & fillColor = DEFAULT_FILL_COLOR,
	const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
	float outlineThikness = 1.f
)
	: CShape(
		ShapeType::Rectangle,
		position,
		size,
		fillColor,
		outlineColor,
		outlineThikness
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

VertexList CRectangle::GetVertices() const
{
	return GetFrameVertices();
}

void CRectangle::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}