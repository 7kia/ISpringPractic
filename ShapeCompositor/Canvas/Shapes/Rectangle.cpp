#include "stdafx.h"
#include "Rectangle.h"

CRectangle::CRectangle(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(position, size, fillColor, outlineColor) {
}

bool CRectangle::IsPointIntersection(const Vec2f point) const
{
	const RECT ownRect = GetOwnRect();
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

void CRectangle::Draw(IRenderShape & renderer) const
{
	renderer.Render(*this);
}