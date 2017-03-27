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
	SRectF ownRect = GetFrameRect(GetSize(), GetPosition());
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
	const SRectF ownRect = GetFrameRect(GetSize(), GetPosition());

	return{
		Vec2f(ownRect.left, ownRect.top)
		, Vec2f(ownRect.right, ownRect.top)
		, Vec2f(ownRect.right, ownRect.bottom)
		, Vec2f(ownRect.left, ownRect.bottom)
	};
}

void CRectangle::Accept(IObjectVisitor & renderer) const
{
	renderer.Visit(*this);
}