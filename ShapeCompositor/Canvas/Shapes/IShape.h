#pragma once

#include "ShapeAttributes.h"
#include "ShapeVisitor.h"


enum class ShapeType
{
	Triangle
	, Rectangle
	, Ellipse
};

// TODO  : see need it
struct SShapeData
{
	SShapeData(
		const ShapeType type = ShapeType::Rectangle
		, const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);

	bool operator==(const SShapeData & shapeData) const;

	Vec2f position;
	SSize size;
	ShapeType type;
	Color fillColor;
	Color outlineColor;
};


class IShapeVisitor;
class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// Inner Color
	virtual void SetFillColor(Color color) = 0;
	virtual Color GetFillColor() const = 0;
	// Outer Color
	virtual void SetOutlineColor(Color color) = 0;
	virtual Color GetOutlineColor() const = 0;
	// Get shape data
	virtual SShapeData GetShapeData() const = 0;
	virtual void SetShapeData(SShapeData const & data) = 0;

	// Type
	virtual ShapeType GetType() const = 0;

	// For draw
	virtual void Accept(IShapeVisitor & visitor) const = 0;

};