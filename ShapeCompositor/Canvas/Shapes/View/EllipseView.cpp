#include "stdafx.h"
#include "EllipseView.h"

bool CEllipseView::IsPointIntersection(const Vec2f point) const
{
	const float a = powf(m_size.width / 2.f, 2.f);
	const float b = powf(m_size.height / 2.f, 2.f);
	const float x = powf((point.x - m_position.x), 2.f);
	const float y = powf((point.y - m_position.y), 2.f);

	return (x / a) + (y / b) <= 1.f;
}

CEllipseView::CEllipseView(
	const Vec2f position,
	const SSize size,
	const Color & fillColor,
	const Color & outlineColor,
	float outlineThikness
)
	: CShapeView(
		position,
		size,
		fillColor,
		outlineColor,
		outlineThikness
	)
{
}

void CEllipseView::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}