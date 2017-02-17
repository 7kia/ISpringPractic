#pragma once

#include "AllShapes.h"
#include "../ShapeRenderer.h"

#include <vector>

class CShapeFactory
{
public:
	CShapeFactory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CShapePtr CreateShape(const SShapeData & data, CShapeRender & shapeRenderer) const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};