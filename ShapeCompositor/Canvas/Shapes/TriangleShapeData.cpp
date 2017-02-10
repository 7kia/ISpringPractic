#include "stdafx.h"
#include "TriangleShapeData.h"

CTriangleShapeData::CTriangleShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShapeModel(position, size, fillColor, outlineColor)
{
}

void CTriangleShapeData::Accept(IRenderShapeVisitor & visitor) const
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

