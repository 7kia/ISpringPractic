#pragma once

#include "D2DObjectRenderer.h"
#include "MouseEventHandler.h"
#include "SelectedShape.h"
#include "CanvasModel.h"

CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector);

enum class CursorType
{
	SIZENWSE,
	SIZENESW,
	SIZEALL,
	ARROW
};

class CCanvasView 
	: public IMouseEventHandler
	//, public IShapeViewManipulator
{
public:
	CCanvasView();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void Draw(IShapeRenderer & renderer);

	CFrame GetFrameSelectedShape() const;
	CFrame GetOldFrameSelectedShape() const;
	size_t GetIndexSelectedShape() const;

	bool HaveSelectedShape() const;
	void ResetSelectedShapeUpdateParameters();

	void AddShapeView(const CShapeViewPtr & pView, size_t insertIndex);
	void DeleteShapeView(size_t index);

	bool DeleteSelectedShape();
	void ResetSelectShapePtr();

	void SetBoundingRect(const D2D1_RECT_F & rect);
	// Signals
	signal::Connection DoOnDeleteShape(std::function<void(size_t)> const & action);
	signal::Connection DoOnChangeRectShape(std::function<void(const CFrame, size_t)> const & action);
	//--------------------------------------------
	// IMouseEventHandler
	bool HandleLButtonDown(const Vec2f  point) override;
	bool HandleLButtonUp(const Vec2f  point) override;
	bool HandleRButtonUp(const Vec2f  point) override;
	bool HandleMouseMove(const Vec2f  point) override;
	//--------------------------------------------

	CursorType ChangeCursor(const Vec2f & position);
private:
	void ChangeSelectedShape(const Vec2f & mousePos);

	size_t GetShapeIndex(const CShapeViewPtr & shapeView) const;

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