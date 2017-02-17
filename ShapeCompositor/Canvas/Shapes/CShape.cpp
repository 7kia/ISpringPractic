#include "stdafx.h"
#include "CShape.h"

SShapeData::SShapeData(
	const TypeShape type
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

SPresenterData::SPresenterData()
{
}

SPresenterData::SPresenterData(Vec2f position, SSize size)
	: position(position)
	, size(size)
{
}

CShape::CShape(
	const TypeShape type
	, const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: IShape()
	, IIsPointIntersection()
	, m_type(type)
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

RECT CShape::GetOwnRect() const
{
	SSize shapeSize = GetSize();
	Vec2f shapePosition = GetPosition();
	RECT rect;
	rect.left = LONG(shapePosition.x - shapeSize.width / 2.f);
	rect.right = LONG(shapePosition.x + shapeSize.width / 2.f);
	rect.bottom = LONG(shapePosition.y + shapeSize.height / 2.f);
	rect.top = LONG(shapePosition.y - shapeSize.height / 2.f);

	return rect;
}

TypeShape CShape::GetShape() const
{
	return m_type;
}

std::vector<Vec2f> CShape::GetFrameVertices() const
{
	RECT frame = GetOwnRect();
	return{
		Vec2f(float(frame.left), float(frame.bottom))// Left bootom
		, Vec2f(float(frame.right), float(frame.bottom))// Right bootom
		, Vec2f(float(frame.right), float(frame.top))// Right top
		, Vec2f(float(frame.left), float(frame.top))// Left top
	};
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
