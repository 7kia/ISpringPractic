#pragma once

#include "Shapes/ShapeAttributes.h"

class IMouseEventHandler
{
public:
	virtual ~IMouseEventHandler() = default;

	virtual bool HandleLButtonDown(const Vec2f  point)= 0;
	virtual bool HandleLButtonUp(const Vec2f  point) = 0;
	virtual bool HandleRButtonUp(const Vec2f  point) = 0;
	virtual bool HandleMouseMove(const Vec2f  point) = 0;
};