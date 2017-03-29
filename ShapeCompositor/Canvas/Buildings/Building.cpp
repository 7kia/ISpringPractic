#include "stdafx.h"
#include "Building.h"

CBuilding::CBuilding(
	const CBuildingType::Type type
	, const Vec2f position
	, const SSize size
	, const Color fillColor 
	, const Color outlineColor
)
	: m_type(type)
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
