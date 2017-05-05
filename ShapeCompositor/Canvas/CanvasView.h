#pragma once

#include "D2DObjectRenderer.h"
#include "MouseEventHandler.h"
#include "SelectedShape.h"
#include "CanvasModel.h"

CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector);


class CCanvasView : public IMouseEventHandler
{
public:
	CCanvasView();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void Draw(IShapeRenderer & renderer);

	void AddShapeView(CShapeViewPtr & pView, size_t insertIndex);
	//--------------------------------------------
	// Signals
	signal::Connection DoOnDeleteShape(std::function<void(size_t)> const & action);
	signal::Connection DoOnChangeRectShape(std::function<void(const CFrame, size_t)> const & action);

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
	void CreateChangeRectCommand();
	void ChangeSelectedShape(const Vec2f & mousePos);

	size_t GetShapeIndex(const CShapeViewPtr & shapeView);

	signal::Signal<void(size_t)> m_deleteShape;
	signal::Signal<void(const CFrame, size_t)> m_createChangeRectCommand;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CSelectedShape m_selectedShape;
	CFrame m_oldFrame;

	CShapeViewPtr m_canvasBorder;
	std::vector<CShapeViewPtr> m_shapeViews;
};