#include "stdafx.h"
#include "Triangle.h"

CTriangle::CTriangle(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CShape(
		TypeShape::Triangle
		, position
		, size
		, fillColor
		, outlineColor
	)
	, IHaveVertex()
{
}

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


std::vector<Vec2f> CTriangle::GetVertices() const
{
	return{
		Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)
		, Vec2f(m_position.x, m_position.y - m_size.height / 2.f)
	};
}

bool CTriangle::IsPointIntersection(const Vec2f point) const
{
	auto verteces = GetVertices();

	return PointIsInsideTriangle(verteces[2], verteces[1], verteces[0], point);
}

void CTriangle::Draw(IRenderShape & renderer) const
{
	renderer.Render(*this);
}