#include "stdafx.h"
#include "RectangleShape.h"

CRectangleShape::CRectangleShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: CShape(position, size, fillColor, outlineColor)
	, CRectangle(size)
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
