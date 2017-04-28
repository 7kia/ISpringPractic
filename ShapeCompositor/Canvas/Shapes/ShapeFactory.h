#pragma once

#include "AllShapes.h"

#include <vector>

class CShapeFactory
{
public:
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	static CShapePtr CreateShape(const SShapeData & data);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};