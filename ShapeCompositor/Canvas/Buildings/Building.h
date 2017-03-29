#pragma once

#include "Canvas\Shapes\Rectangle.h"
#include "BuildingType.h"

static const Color BUILDING_OUTLINE_COLOR = Color(0.f, 0.f, 0.f);
static const Color BUILDING_FILL_COLOR = Color(0.95f, 0.55f, 0.55f);

class CBuilding
	: public CRectangle
{
public:
	CBuilding(
		const CBuildingType::Type type
		, const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = BUILDING_FILL_COLOR
		, const Color outlineColor = BUILDING_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IDrawable

	void Accept(IShapeVisitor & renderer) const override;
	//--------------------------------------------

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CBuildingType::Type m_type;
};