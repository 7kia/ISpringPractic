#pragma once

#include "Shapes/ShapeAttributes.h"


class IMouseEventHandler
{
public:
	virtual ~IMouseEventHandler() = default;

	virtual bool HandleLButtHandleDown(const Vec2f  point )= 0;
	virtual bool HandleLButtHandleUp(const Vec2f  point) = 0;
	virtual bool HandleRButtHandleUp(const Vec2f  point) = 0;
	virtual bool HandleMouseMove(const Vec2f  point) = 0;
};