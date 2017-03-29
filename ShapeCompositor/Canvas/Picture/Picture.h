#pragma once

#include "Canvas\Shapes\Rectangle.h"
#include <d2d1.h>

class CPicture : public CRectangle
{
public:
	CPicture(
		ID2D1Bitmap * pTexture = nullptr
		, const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	// IDrawable

	void Accept(IShapeVisitor & renderer) const override;
	//--------------------------------------------

	ID2D1Bitmap * GetTexture() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ID2D1Bitmap * m_pTexture = nullptr;
};