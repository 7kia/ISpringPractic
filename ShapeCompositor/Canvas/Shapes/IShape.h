#pragma once

#include "ShapeAttributes.h"

class IShape
{
public:
	virtual ~IShape() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	// Position
	virtual void SetPosition(Vec2f position) = 0;
	virtual Vec2f GetPosition() const = 0;
	// Inner Color
	virtual void SetInnerColor(Color color) = 0;
	virtual Color GetInnerColor() const = 0;
	// Outer Color
	virtual void SetOuterColor(Color color) = 0;
	virtual Color GetOuterColor() const = 0;

	// TODO :
	// Visual part
};