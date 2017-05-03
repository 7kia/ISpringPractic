#pragma once

#include "Canvas\Shapes\Rectangle.h"
#include "PictureModel.h"
#include <d2d1.h>

class CPicture : public CRectangle
{
public:
	CPicture() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShapeView
	void Accept(IShapeVisitor & visitor) const override;
	//--------------------------------------------
	ID2D1Bitmap * GetTexture() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ID2D1Bitmap * m_pTexture = nullptr;
};