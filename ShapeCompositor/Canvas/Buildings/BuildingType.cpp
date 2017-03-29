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

void CBuildingType::SetTextureName(const std::string & textureName)
{
	m_textureName = textureName;
}

std::string CBuildingType::GetTextureName() const
{
	return m_textureName;
}

void CBuildingType::SetSize(const SSize & size)
{
	m_size = size;
}

SSize CBuildingType::GetSize() const
{
	return m_size;
}
