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
	// Thickness outline
	virtual void SetOutlineThickness(const float thickness) = 0;
	virtual float GetOutlineThickness() const = 0;

	virtual void Accept(IShapeVisitor & visitor) const = 0;
};