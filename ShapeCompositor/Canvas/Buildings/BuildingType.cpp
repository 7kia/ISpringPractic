#include "stdafx.h"
#include "BuildingType.h"

CBuildingType::CBuildingType()
{
}

void CBuildingType::SetName(const std::string & name)
{
	m_name = name;
}

std::string CBuildingType::GetName() const
{
	return m_name;
}


void CBuildingType::SetSize(const SSize & size)
{
	m_size = size;
}

SSize CBuildingType::GetSize() const
{
	return m_size;
}

void CBuildingType::SetTexture(ID2D1Bitmap * pTexture)
{
	m_pTexture = pTexture;
}

ID2D1Bitmap * CBuildingType::GetTexture() const
{
	return m_pTexture;
}
