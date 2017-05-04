#include "stdafx.h"
#include "GlobalFunctions.h"
#include "RectangleView.h"


bool CRectangleView::IsPointIntersection(const Vec2f point) const
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

VertexList CRectangleView::GetVertices() const
{
	return GetFrameVertices();
}

void CRectangleView::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}