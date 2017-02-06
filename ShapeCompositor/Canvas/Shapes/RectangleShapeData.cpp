#include "stdafx.h"
#include "RectangleShapeData.h"

CRectangleShapeData::CRectangleShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: CShapeData(position, size, fillColor, outlineColor)
	, IHaveVertex()
{
}


void CRectangleShapeData::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

std::vector<Vec2f> CRectangleShapeData::GetVertices() const
{
	Vec2f m_position = GetPosition();

	return{ 
		 Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Left bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Right bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Right top
		, Vec2f(m_position.x - m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Left top
	};
}
