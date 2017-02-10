#include "stdafx.h"
#include "CShapeModel.h"

CShapeModel::CShapeModel(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: IShape()
	, CShapeData(position, size, fillColor, outlineColor)
	, IObserver<SShapeData>()
	, CObservable<const CShapeModel *>()
	, IHaveVertex()
{
}

void CShapeModel::SetPosition(Vec2f position)
{
	m_position = position;
}

Vec2f CShapeModel::GetPosition() const
{
	return m_position;
}

void CShapeModel::SetFillColor(Color color)
{
	m_fillColor = color;
}

Color CShapeModel::GetFillColor() const
{
	return m_fillColor;
}

void CShapeModel::SetOutlineColor(Color color)
{
	m_outlineColor = color;
}

Color CShapeModel::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShapeModel::SetSize(SSize size)
{
	m_size = size;
}

SSize CShapeModel::GetSize() const
{
	return m_size;
}

RECT CShapeModel::GetOwnRect() const
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

void CShapeModel::Update(SShapeData const & data)
{
	m_position = data.position;
	m_size = data.size;
	m_fillColor = data.fillColor;
	m_outlineColor = data.outlineColor;

	NotifyObservers();
}

const CShapeModel * CShapeModel::GetChangedData() const
{
	return this;
}


std::vector<Vec2f> CShapeModel::GetVertices() const
{
	return GetFrameVertices();
}

SShapeData::SShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: position(position)
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

CShapeData::CShapeData(
	const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor
)
	: m_position(position)
	, m_size(size)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
{
}

std::vector<Vec2f> CShapeData::GetFrameVertices() const
{
	return{
		Vec2f(m_position.x - m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Left bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y + m_size.height / 2.f)// Right bootom
		, Vec2f(m_position.x + m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Right top
		, Vec2f(m_position.x - m_size.width / 2.f, m_position.y - m_size.height / 2.f)// Left top
	};
}
