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
	CShapePtr CreateShape(const SShapeData & data, CD2DObjectRenderer & shapeRenderer) const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};