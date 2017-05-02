#include "stdafx.h"
#include "Picture.h"

CPicture::CPicture(
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size
)
	: m_pTexture(pTexture)
	, CRectangle(position,size)
{
	m_type = ShapeType::Picture;
}

void CPicture::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}

ID2D1Bitmap * CPicture::GetTexture() const
{
	return m_pTexture;
}

SPictureData CPicture::GetPictureData() const
{
	return SPictureData(m_pTexture, m_position, m_size);
}

SPictureData::SPictureData(
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size
) 
	: pTexture(pTexture)
	, position(position)
	, size(size)
{
}
