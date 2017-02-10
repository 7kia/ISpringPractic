#pragma once

#include "Shapes\ShapeFactory.h"

class CShapeTypeDefiner
{
public:
	CShapeTypeDefiner() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	TypeShape GetType(const CRectanglePresenter & shape);
	TypeShape GetType(const CEllipsePresenter & shape);
	TypeShape GetType(const CTrianglePresenter & shape);
};