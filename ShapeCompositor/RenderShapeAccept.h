#pragma once

#include "RenderShapeVisitor.h"

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(IRenderShape & renderer) const {};// TODO : must be = 0
};