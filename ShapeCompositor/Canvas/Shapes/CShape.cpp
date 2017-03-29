#include "stdafx.h"
#include "CShape.h"

SShapeData::SShapeData(
	const ShapeType type
	, const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: type(type)
	, position(position)
	, size(size)
	, fillColor(fillColor)
	, outlineColor(outlineColor)
{
}

bool SShapeData::operator==(const SShapeData & shapeData) const
{
	return (position == shapeData.position)
		&& (size == shapeData.size)
		&& (type == shapeData.type)
		&& (fillColor == shapeData.fillColor)
		&& (outlineColor == shapeData.outlineColor);
}

CShape::CShape(
	const ShapeType type
	, const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: CFrame(position, size)
	, m_type(type)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
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


ShapeType CShape::GetType() const
{
	return m_type;
}

SShapeData CShape::GetShapeData() const
{
	SShapeData info;
	info.type = m_type;
	info.position = m_position;
	info.size = m_size;
	info.fillColor = m_fillColor;
	info.outlineColor = m_outlineColor;
	return info;
}

void CShape::SetShapeData(SShapeData const & data)
{
	m_type = data.type;
	m_position = data.position;
	m_size = data.size;
	m_fillColor = data.fillColor;
	m_outlineColor = data.outlineColor;
}

