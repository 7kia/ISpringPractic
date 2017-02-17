#include "stdafx.h"
#include "ShapeTypeDefiner.h"

TypeShape CShapeTypeDefiner::GetType(const CRectangle & shape)
{
	return TypeShape::Rectangle;
}

TypeShape CShapeTypeDefiner::GetType(const CEllipse & shape)
{
	return TypeShape::Ellipse;
}

TypeShape CShapeTypeDefiner::GetType(const CTriangle & shape)
{
	return TypeShape::Triangle;
}
