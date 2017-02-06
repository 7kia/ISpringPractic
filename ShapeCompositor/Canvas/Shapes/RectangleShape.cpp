#include "stdafx.h"
#include "RectangleShape.h"

CRectangleShape::CRectangleShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: CShapeData(position, size, fillColor, outlineColor)
	, IHaveVertex()
{
}


void CRectangleShape::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

bool CRectangleShape::IsPointIntersection(const Vec2f point) const
{
	return IsBetween(point.x, m_position.x - m_size.width / 2.f, m_position.x + m_size.width / 2.f)
		&& IsBetween(point.y, m_position.y - m_size.height / 2.f, m_position.y + m_size.height / 2.f);
}

std::vector<Vec2f> CRectangleShape::GetVertices() const
{
	Vec2f m_position = GetPosition();

	return{ 
		 Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Left bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Right bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Right top
		, Vec2f(m_position.x - m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Left top
	};
}
