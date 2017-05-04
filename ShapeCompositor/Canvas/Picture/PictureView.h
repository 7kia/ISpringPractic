#pragma once

#include "Canvas\Shapes\RectangleView.h"
#include "PictureModel.h"
#include <d2d1.h>

class CPictureView : public CRectangleView
{
public:
	CPictureView() = default;
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