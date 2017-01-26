#include "stdafx.h"
#include "CShape.h"

CShape::CShape(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: IShape()
	, m_position(position)
	, m_size(size)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

void CShape::SetPosition(Vec2f position)
{
	m_position = position;
}

Vec2f CShape::GetPosition() const
{
	return m_position;
}

void CShape::SetFillColor(Color color)
{
	m_fillColor = color;
}

Color CShape::GetFillColor() const
{
	return m_fillColor;
}

void CShape::SetOutlineColor(Color color)
{
	m_outlineColor = color;
}

Color CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetSize(SSize size)
{
	m_size = size;
}

SSize CShape::GetSize() const
{
	return m_size;
}
