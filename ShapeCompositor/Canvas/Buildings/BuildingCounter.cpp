#include "stdafx.h"
#include "BuildingCounter.h"

CBuildingCounter::CBuildingCounter(
	const CBuildingType::Type type
	, const size_t max)
	: m_buildingType(type)
	, m_maxCount(max)
{
}

bool CBuildingCounter::Increment()
{
	if ((m_count + 1) > m_maxCount)
	{
		return false;
	}

	++m_count;
	return true;
}

bool CBuildingCounter::Decrement()
{
	if (m_count == 0)
	{
		return false;
	}
	
	--m_count;
	return true;
}


