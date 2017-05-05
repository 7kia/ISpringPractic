#pragma once

#include "Canvas\Shapes\AllViewShapes.h"


class IShapeRenderer
{
public:
	virtual ~IShapeRenderer() = default;

	virtual void Draw(const IShape & shape) = 0;
};