#include "stdafx.h"
#include "PictureView.h"

CPictureView::CPictureView(
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size
)
	: CRectangleView(position, size)
	, m_pTexture(pTexture)
{
}

void CPictureView::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}

ID2D1Bitmap * CPictureView::GetTexture() const
{
	return m_pTexture;
}

