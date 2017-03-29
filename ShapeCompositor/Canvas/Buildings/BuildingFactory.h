#pragma once

#include "Building.h"

class CBuildingFactory
{
public:
	CBuildingFactory() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CShapePtr CreateBuilding(CBuildingType* type, const Vec2f position) const;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};