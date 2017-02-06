#include "stdafx.h"
#include "CShape.h"

CShapeData::CShapeData(
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

void CShapeData::SetPosition(Vec2f position)
{
	m_position = position;
}

Vec2f CShapeData::GetPosition() const
{
	return m_position;
}

void CShapeData::SetFillColor(Color color)
{
	m_fillColor = color;
}

Color CShapeData::GetFillColor() const
{
	return m_fillColor;
}

void CShapeData::SetOutlineColor(Color color)
{
	m_outlineColor = color;
}

Color CShapeData::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShapeData::SetSize(SSize size)
{
	m_size = size;
}

SSize CShapeData::GetSize() const
{
	return m_size;
}

RECT CShapeData::GetOwnRect() const
{
	SSize shapeSize = GetSize();
	Vec2f shapePosition = GetPosition();
	RECT rect;
	rect.left = shapePosition.x - shapeSize.width / 2;
	rect.right = shapePosition.x + shapeSize.width / 2;
	rect.bottom = shapePosition.y - shapeSize.height / 2;
	rect.top = shapePosition.y + shapeSize.height / 2;

	return rect;
}
