#include "stdafx.h"
#include "CircleShape.h"

CCircleShape::CCircleShape()
	: CShape()
	, CCircle()

{
}

void CCircleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}
