#pragma once

#include "Canvas\Shapes\View\RectangleView.h"
#include "PictureModel.h"
#include <d2d1.h>

class CPictureView : public CRectangleView
{
public:
	CPictureView() = default;
	CPictureView(
		ID2D1Bitmap * pTexture,
		const Vec2f position,
		const SSize size
	);

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