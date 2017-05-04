#pragma once

#include "Canvas\D2DObjectRenderer.h"
#include "MouseEventHandler.h"

bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapeViewPtr> & shapes);


class CCanvasView : public IMouseEventHandler
{
public:
	CCanvasView();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void Draw(IShapeRenderer & renderer);

	//--------------------------------------------
	// Signals
	signal::Connection DoOnDeleteShape(std::function<void(size_t)> const & action);

	//--------------------------------------------
	// NameInterface
	bool HandleLButtonDown(const Vec2f  point) override;
	bool HandleLButtonUp(const Vec2f  point) override;
	bool HandleRButtonUp(const Vec2f  point) override;
	bool HandleMouseMove(const Vec2f  point) override;
	//--------------------------------------------
	bool DeleteSelectedShape();

	void ResetSelectShapePtr();
	void SetBoundingRect(const D2D1_RECT_F & rect);

private:
	void ChangeCursor(const Vec2f & position);
	void CreateCommandForSelectedShape();

	size_t GetShapeIndex(const CShapeViewPtr & shapeView);

	signal::Signal<void(size_t)> m_deleteShape;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CSelectedShape m_selectedShape;
	CFrame m_oldFrame;

	CShapeViewPtr m_canvasBorder;
	std::vector<CShapeViewPtr> m_shapeViews;
};