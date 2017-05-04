#include "stdafx.h"
#include "PictureView.h"

CPictureView::CPictureView(
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size
)
	: m_pTexture(pTexture)
	, CRectangleView(position,size)
{
	m_type = ShapeType::Picture;
}

void CPictureView::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}

ID2D1Bitmap * CPictureView::GetTexture() const
{
	return m_pTexture;
}

SPictureData CPictureView::GetPictureData() const
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
