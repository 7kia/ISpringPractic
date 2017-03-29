#include "stdafx.h"
#include "Building.h"

CBuilding::CBuilding(
	CBuildingType* pType
	, const Vec2f position
	, const SSize size
	, const Color fillColor 
	, const Color outlineColor
)
	: m_pType(pType)
	, CRectangle(
		position
		, size
		, fillColor
		, outlineColor
	)
{
}

void CBuilding::Accept(IShapeVisitor & renderer) const
{
	renderer.Visit(*this);
}

void CBuilding::SetBuildingType(CBuildingType * pType)
{
	m_pType = pType;
}

CBuildingType * CBuilding::GetBuildingType() const
{
	return m_pType;
}
