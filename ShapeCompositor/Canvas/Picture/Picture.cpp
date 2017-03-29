#include "stdafx.h"
#include "Picture.h"

CPicture::CPicture(
	const std::string textureName
	, const Vec2f position
	, const SSize size
	, const Color fillColor
	, const Color outlineColor

)
	: m_textureName(textureName)
	, CRectangle(
		position
		, size
		, fillColor
		, outlineColor
	)
{
}

void CPicture::Accept(IShapeVisitor & renderer) const
{
	renderer.Visit(*this);
}
