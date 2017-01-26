#pragma once

#include "ShapeAttributes.h"
#include "RenderShapeAccept.h"

class IShape
	: public IRenderShapeAccept
	, public IIsPointIntersection
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

	// TODO :
	// Visual part
};