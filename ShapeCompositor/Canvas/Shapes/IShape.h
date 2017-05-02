#pragma once

#include "ShapeAttributes.h"
#include "ShapeVisitor.h"


enum class ShapeType
{
	Triangle,
	Rectangle,
	Ellipse,
	Picture,
};

// TODO  : see need it
struct SShapeData
{
	SShapeData(
		const ShapeType type = ShapeType::Rectangle,
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE,
		const Color & fillColor = DEFAULT_FILL_COLOR,
		const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
		float outlineThikness = 1.f
	);

	bool operator==(const SShapeData & shapeData) const;

	Vec2f position;
	SSize size;
	ShapeType type;
	Color fillColor;
	Color outlineColor;
	float outlineThikness = 1.f;
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
	virtual void SetFillColor(const Color & color) = 0;
	virtual Color GetFillColor() const = 0;
	// Outer Color
	virtual void SetOutlineColor(const Color &  color) = 0;
	virtual Color GetOutlineColor() const = 0;
	// Thikness outline
	virtual void SetOutlineThickness(const float thickness) = 0;
	virtual float GetOutlineThickness() const = 0;
	// Get shape data
	virtual SShapeData GetShapeData() const = 0;
	virtual void SetShapeData(const SShapeData  & data) = 0;

	// Type
	virtual ShapeType GetType() const = 0;

	// For draw
	virtual void Accept(IShapeVisitor & visitor) const = 0;

};