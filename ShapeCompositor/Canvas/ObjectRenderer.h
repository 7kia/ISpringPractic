#pragma once

#include "Canvas\Shapes\AllShapes.h"


class IObjectRenderer
{
public:
	virtual ~IObjectRenderer() = default;

	virtual void Draw(const IDrawable & shape) = 0;
};