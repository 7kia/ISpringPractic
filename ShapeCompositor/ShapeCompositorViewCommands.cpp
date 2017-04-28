#include "stdafx.h"
#include "ShapeCompositorView.h"


signal::Connection CShapeCompositorView::DoOnGetCanvasView(std::function<CShapePtr()> const & action)
{
	return m_getCanvasView.connect(action);
}

signal::Connection CShapeCompositorView::DoOnGetCanvasShapes(std::function<std::vector<CShapePtr>()> const & action)
{
	return m_getCanvasShapes.connect(action);
}

signal::Connection CShapeCompositorView::DoOnCreatePicture(std::function<void()> const & action)
{
	return m_createPicture.connect(action);
}

signal::Connection CShapeCompositorView::DoOnUndoCommand(std::function<void()> const & action)
{
	return m_undoCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnRedoCommand(std::function<void()> const & action)
{
	return m_redoCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnCreateShapeCommand(std::function<void(ShapeType, CSelectedShape)> const & action)
{
	return m_createShapeCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSetRenderTargetForImageFactory(std::function<void(ID2D1HwndRenderTarget*)> const & action)
{
	return m_setRenderTargetForImageFactory.connect(action);
}
