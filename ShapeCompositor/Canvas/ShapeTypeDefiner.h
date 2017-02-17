#pragma once

#include "Shapes\ShapeFactory.h"

class CShapeTypeDefiner
{
public:
	CShapeTypeDefiner() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	TypeShape GetType(const CRectangle & shape);
	TypeShape GetType(const CEllipse & shape);
	TypeShape GetType(const CTriangle & shape);
};