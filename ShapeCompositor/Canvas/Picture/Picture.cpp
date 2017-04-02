#include "stdafx.h"
#include "Picture.h"

CPicture::CPicture(
	ID2D1Bitmap * pTexture
	, const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: m_pTexture(pTexture)
	, CRectangle(
		position
		, size
		, fillColor
		, outlineColor
	)
{
}

void CPicture::Accept(IShapeVisitor & visitor) const
{
	visitor.Visit(*this);
}

ID2D1Bitmap * CPicture::GetTexture() const
{
	return m_pTexture;
}
