#include "stdafx.h"
#include "PictureModel.h"

CPictureModel::CPictureModel(
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size
)
	: m_pTexture(pTexture)
	, CShapeModel(ShapeType::Picture, position, size)
{
}

ID2D1Bitmap * CPictureModel::GetTexture() const
{
	return m_pTexture;
}
