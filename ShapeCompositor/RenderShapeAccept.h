#pragma once

#include "RenderShapeVisitor.h"

class IRenderShapeAccept
{
public:
	virtual ~IRenderShapeAccept() = default;

	virtual void Accept(IRenderShapeVisitor & visitor) = 0;
};