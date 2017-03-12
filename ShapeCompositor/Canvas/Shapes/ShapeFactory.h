#pragma once

#include "AllShapes.h"

#include <vector>

class CShapeFactory
{
public:
	CShapeFactory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CShapePtr CreateShape(const SShapeData & data) const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};