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
	RECT ownRect = GetOwnRect();
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

std::vector<Vec2f> CRectangle::GetVertices() const
{
	const RECT ownRect = GetOwnRect();

	return{
		Vec2f(float(ownRect.left),float(ownRect.top))
		, Vec2f(float(ownRect.right),float(ownRect.top))
		, Vec2f(float(ownRect.right),float(ownRect.bottom))
		, Vec2f(float(ownRect.left),float(ownRect.bottom))
	};
}

void CRectangle::Accept(IObjectVisitor & renderer) const
{
	renderer.Visit(*this);
}