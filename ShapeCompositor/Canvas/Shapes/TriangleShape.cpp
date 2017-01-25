#include "stdafx.h"
#include "TriangleShape.h"

CTriangleShape::CTriangleShape(Vec2f const & position
								, float width
								, float height
)
	: CShape()
	, IHaveVertex()
{
	m_verteces.push_back(Vec2f(position.x - width / 2.f, position.y + height / 2.f));
	m_verteces.push_back(Vec2f(position.x + width / 2.f, position.y + height / 2.f));
	m_verteces.push_back(Vec2f(position.x, position.y - height / 2.f));
}

void CTriangleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

std::vector<Vec2f> CTriangleShape::GetVertices() const
{
	return m_verteces;
}
