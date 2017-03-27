#include "stdafx.h"
#include "VertexGenerator.h"

std::vector<Vec2f> CVertexGenerator::GetVertices(const IShape & shape)
{
	shape.Accept(*this);
	return m_generatedVerteces;
}

void CVertexGenerator::Visit(const CRectangle & shape)
{
	const SRectF ownRect = GetFrameRect(shape.GetSize(), shape.GetPosition());

	m_generatedVerteces = {
		Vec2f(ownRect.left, ownRect.top)
		, Vec2f(ownRect.right, ownRect.top)
		, Vec2f(ownRect.right, ownRect.bottom)
		, Vec2f(ownRect.left, ownRect.bottom)
	};
}

void CVertexGenerator::Visit(const CEllipse & shape)
{
	// TODO : Direct2d have need functional
}

void CVertexGenerator::Visit(const CTriangle & shape)
{
	const Vec2f position = shape.GetPosition();
	const SSize size = shape.GetSize();
	Vec2f first = Vec2f(position.x - size.width / 2.f, position.y + size.height / 2.f);
	Vec2f second = Vec2f(position.x + size.width / 2.f, position.y + size.height / 2.f);
	Vec2f third = Vec2f(position.x, position.y - size.height / 2.f);

	// For vertex invertion
	if (size.width < 0.f)
	{
		//result = { second, first, third };
		std::swap(first, second);
	}
	if (size.height < 0.f)
	{
		//result = { third, second, first };
		std::swap(first, third);
	}
	m_generatedVerteces = { first, second, third };
}
