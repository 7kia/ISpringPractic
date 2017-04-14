#include "stdafx.h"
#include "Triangle.h"

namespace
{

	float dot(Vec2f first, Vec2f second)
	{
		return (first.x * second.x) + (first.y * second.y);
	}

	// Check if the point p is on the left side of the line p0p1
	bool PointIsOnTheLeft(Vec2f p0, Vec2f p1, Vec2f p)
	{
		Vec2f p0p1 = p1 - p0;
		// find the orthogonal vector to p0p1
		Vec2f n = Vec2f(-p0p1.y, p0p1.x);
		// Find the dot product between n and (p - p0)
		return dot(p - p0, n) >= 0.0f;
	}

	bool PointIsInsideTriangle(Vec2f p0, Vec2f p1, Vec2f p2, Vec2f p)
	{
		bool f1 = PointIsOnTheLeft(p0, p1, p);
		bool f2 = PointIsOnTheLeft(p1, p2, p);
		bool f3 = PointIsOnTheLeft(p2, p0, p);

		return PointIsOnTheLeft(p0, p1, p) &&
			PointIsOnTheLeft(p1, p2, p) &&
			PointIsOnTheLeft(p2, p0, p);
	}

}

CTriangle::CTriangle(
	const Vec2f m_position
	, const SSize m_size
	, const Color & fillColor
	, const Color & outlineColor
	, float outlineThikness
)
	: CShape(
		ShapeType::Triangle
		, m_position
		, m_size
		, fillColor
		, outlineColor
		, outlineThikness
	)
{
}

bool CTriangle::IsPointIntersection(const Vec2f point) const
{
	auto vertices = GetVertices();

	return PointIsInsideTriangle(vertices[2], vertices[1], vertices[0], point);
}

VertexList CTriangle::GetVertices() const
{
	Vec2f first = Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f);
	Vec2f second = Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f);
	Vec2f third = Vec2f(m_position.x, m_position.y - m_size.height / 2.f);

	// For vertex invertion
	if (m_size.width < 0.f)
	{
		//result = { second, first, third };
		std::swap(first, second);
	}
	if (m_size.height < 0.f)
	{
		//result = { third, second, first };
		std::swap(first, third);
	}

	return { first, second, third };
}

void CTriangle::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}