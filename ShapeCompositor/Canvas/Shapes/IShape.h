#pragma once

#include "stdafx.h"

class IShape
{
public:
	virtual ~IShape() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	virtual void Draw() = 0;

	// Position
	virtual void SetPosition(D2D1_POINT_2F position) = 0;
	virtual D2D1_POINT_2F GetPosition() const = 0;
	// Inner Color
	virtual void SetInnerColor(D2D1_COLOR_F color) = 0;
	virtual D2D1_COLOR_F GetInnerColor() const = 0;
	// Outer Color
	virtual void SetOuterColor(D2D1_COLOR_F color) = 0;
	virtual D2D1_COLOR_F GetOuterColor() const = 0;

	// TODO :
	// Visual part
};