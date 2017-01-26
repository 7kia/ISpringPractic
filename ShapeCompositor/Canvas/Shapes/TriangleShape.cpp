#include "stdafx.h"
#include "TriangleShape.h"

CTriangleShape::CTriangleShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(position, size, fillColor, outlineColor)
	, IHaveVertex()
{
}

void CTriangleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

std::vector<Vec2f> CTriangleShape::GetVertices() const
{
	return {
		Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x, m_position.y - m_size.height / 2.f)
	};
}
