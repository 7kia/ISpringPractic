#include "stdafx.h"
#include "BuildingFactory.h"

CShapePtr CBuildingFactory::CreateBuilding(CBuildingType* type, const Vec2f position) const
{
	if (type != nullptr)
	{
	
		return std::make_shared<CBuilding>(
				type
				, position
				, SSize(100.f, 77.f)
				, BUILDING_FILL_COLOR
				, BUILDING_OUTLINE_COLOR
			);
	}
	else
	{
		throw std::runtime_error("The building type not exist");
	}
}
