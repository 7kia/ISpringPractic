#pragma once

#include "Canvas\Shapes\Rectangle.h"
#include <d2d1.h>

struct SPictureData
{
	SPictureData(
		ID2D1Bitmap * pTexture 
		, const Vec2f position
		, const SSize size
	);

	ID2D1Bitmap * pTexture;
	Vec2f position;
	SSize size;
};

class CPicture : public CRectangle
{
public:
	CPicture(
		ID2D1Bitmap * pTexture = nullptr,
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape
	void Accept(IShapeVisitor & visitor) const override;
	//--------------------------------------------
	ID2D1Bitmap * GetTexture() const;
	SPictureData GetPictureData() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ID2D1Bitmap * m_pTexture = nullptr;
};