#pragma once

#include "Canvas\Shapes\AllShapes.h"


class IObjectRenderer
{
public:
	virtual ~IObjectRenderer() = default;

	virtual void Draw(const IShape & shape) = 0;
};