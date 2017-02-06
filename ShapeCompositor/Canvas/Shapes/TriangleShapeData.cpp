#include "stdafx.h"
#include "TriangleShapeData.h"

CTriangleShapeData::CTriangleShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShapeData(position, size, fillColor, outlineColor)
	, IHaveVertex()
{
}

void CTriangleShapeData::Accept(IRenderShapeVisitor & visitor)
{
	visitor.Visit(*this);
}

// TODO : see might transfer the part to other class, mixin(dublicate to CTrianglePresenter)
std::vector<Vec2f> CTriangleShapeData::GetVertices() const
{
	return{
		Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x, m_position.y - m_size.height / 2.f)
	};
}

