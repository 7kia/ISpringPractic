#pragma once

#include "BuildingType.h"

class CBuildingCounter
{
public:
	CBuildingCounter() = default;
	CBuildingCounter(
		const CBuildingType::Type type
		, const size_t max
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool			Increment();
	bool			Decrement();

private:
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	size_t m_maxCount = 0;
	size_t m_count = 0;
	CBuildingType::Type m_buildingType;
};