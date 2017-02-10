#include "stdafx.h"
#include "ShapeTypeDefiner.h"

TypeShape CShapeTypeDefiner::GetType(const CRectanglePresenter & shape)
{
	return TypeShape::Rectangle;
}

TypeShape CShapeTypeDefiner::GetType(const CEllipsePresenter & shape)
{
	return TypeShape::Ellipse;
}

TypeShape CShapeTypeDefiner::GetType(const CTrianglePresenter & shape)
{
	return TypeShape::Triangle;
}
