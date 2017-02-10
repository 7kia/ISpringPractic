#include "stdafx.h"
#include "CShape.h"

CShapeData::CShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: IShape()
	, IObserver<SPresenterData>()
	, CObservable<const CShapeData *>()
	, IHaveVertex()
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
	rect.left = LONG(shapePosition.x - shapeSize.width / 2.f);
	rect.right = LONG(shapePosition.x + shapeSize.width / 2.f);
	rect.bottom = LONG(shapePosition.y + shapeSize.height / 2.f);
	rect.top = LONG(shapePosition.y - shapeSize.height / 2.f);

	return rect;
}

void CShapeData::Update(SPresenterData const & data)
{
	m_position = data.position;
	m_size = data.size;

	NotifyObservers();
}

const CShapeData * CShapeData::GetChangedData() const
{
	return this;
}


std::vector<Vec2f> CShapeData::GetVertices() const
{
	Vec2f m_position = GetPosition();

	return{
		Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Left bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Right bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Right top
		, Vec2f(m_position.x - m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Left top
	};
}

SShapeData::SShapeData()
	: position(Vec2f())
	, size(DEFAULT_SIZE)
	, fillColor(DEFAULT_FILL_COLOR)
	, outlineColor(DEFAULT_OUTLINE_COLOR)
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
