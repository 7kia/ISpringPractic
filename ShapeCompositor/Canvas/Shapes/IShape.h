#pragma once

#include "ShapeAttributes.h"
#include "RenderShapeAccept.h"

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_OUTLINE_COLOR = Color(0.f, 0.f, 0.f);
static const Color DEFAULT_FILL_COLOR = Color(0.45f, 0.75f, 0.55f);

// TODO  : see need it
struct SShapeData
{
	SShapeData(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);

	Vec2f position;
	SSize size;
	Color fillColor;
	Color outlineColor;
};

class IShape
	: public IDrawable
{
public:
	IShape();
	virtual ~IShape() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	// Position
	virtual void SetPosition(Vec2f position) = 0;
	virtual Vec2f GetPosition() const = 0;
	// Inner Color
	virtual void SetFillColor(Color color) = 0;
	virtual Color GetFillColor() const = 0;
	// Outer Color
	virtual void SetOutlineColor(Color color) = 0;
	virtual Color GetOutlineColor() const = 0;
	// Size
	virtual void SetSize(SSize size) = 0;
	virtual SSize GetSize() const = 0;
	// Own rect
	virtual RECT GetOwnRect() const = 0;
	// Get shape data
	virtual SShapeData GetShapeData() const = 0;
	virtual void SetShapeData(SShapeData const & data) = 0;

};