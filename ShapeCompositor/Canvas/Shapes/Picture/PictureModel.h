#pragma once

#include "../Model/ShapeModel.h"


class CPictureModel : public CShapeModel
{
public:
	CPictureModel(
		ID2D1Bitmap * pTexture = nullptr,
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	ID2D1Bitmap * GetTexture() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ID2D1Bitmap * m_pTexture = nullptr;
};