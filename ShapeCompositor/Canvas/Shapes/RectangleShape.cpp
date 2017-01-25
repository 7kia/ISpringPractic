#include "stdafx.h"
#include "RectangleShape.h"

CRectangleShape::CRectangleShape()
	: CShape()
	, CRectangle()
	, IHaveVertex()
{
}

CRectangleShape::CRectangleShape(SSize size)
	: CShape()
	, CRectangle(size)
	, IHaveVertex()
{
}

CRectangleShape::CRectangleShape(float width, float height)
	: CShape()
	, CRectangle(width, height)
	, IHaveVertex()

{
}

void CRectangleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

std::vector<Vec2f> CRectangleShape::GetVertices() const
{
	Vec2f position = GetPosition();
	float width = GetWidth();
	float height = GetHeight();

	return{ 
		 Vec2f(position.x - width / 2.f, position.y + height / 2.f)// Left bootom
		, Vec2f(position.x + width / 2.f, position.y + height / 2.f)// Right bootom
		, Vec2f(position.x + width / 2.f, position.y - height / 2.f)// Right top
		, Vec2f(position.x - width / 2.f, position.y - height / 2.f)// Left top
	};
}
