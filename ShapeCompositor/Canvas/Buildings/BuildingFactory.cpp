#include "stdafx.h"
#include "BuildingFactory.h"

CShapePtr CBuildingFactory::CreateBuilding(const CBuildingType::Type type, const Vec2f position) const
{
	switch (type)
	{
	case CBuildingType::Type::House:
		{
		return std::make_shared<CBuilding>(
				type
				, position
				, SSize(100.f, 77.f)
				, BUILDING_FILL_COLOR
				, BUILDING_OUTLINE_COLOR
			);
		}
		break;
	default:
		throw std::runtime_error("The building type not exist");
		break;
	}
}
