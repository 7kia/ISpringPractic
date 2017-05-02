#include "stdafx.h"
#include "Ellipse.h"

CEllipse::CEllipse(
	const Vec2f position = Vec2f(),
	const SSize size = DEFAULT_SIZE,
	const Color & fillColor = DEFAULT_FILL_COLOR,
	const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
	float outlineThikness = 1.f
)
	: CShape(
		ShapeType::Ellipse,
		position,
		size,
		fillColor,
		outlineColor,
		outlineThikness
	)
{
}

bool CEllipse::IsPointIntersection(const Vec2f point) const
{
	const float a = powf(m_size.width / 2.f, 2.f);
	const float b = powf(m_size.height / 2.f, 2.f);
	const float x = powf((point.x - m_position.x), 2.f);
	const float y = powf((point.y - m_position.y), 2.f);

	return (x / a) + (y / b) <= 1.f;
}

void CEllipse::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}