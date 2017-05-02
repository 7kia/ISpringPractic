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


signal::Connection CShapeCompositorView::DoOnSaveAsDocument(std::function<bool()> const & action)
{
	return m_saveAsDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSaveDocument(std::function<bool()> const & action)
{
	return m_saveDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnOpenDocument(std::function<bool(CSelectedShape &)> const & action)
{
	return m_openDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnNewDocument(std::function<bool()> const & action)
{
	return m_newDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnUndoCommand(std::function<void()> const & action)
{
	return m_undoCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnRedoCommand(std::function<void()> const & action)
{
	return m_redoCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnDeleteShapeCommand(std::function<void(CSelectedShape &)> const & action)
{
	return m_deleteShapeCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnChangeRectCommand(std::function<void(const CFrame, CSelectedShape &)> const & action)
{
	return m_createChangeRectCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnCreateShapeCommand(std::function<void(ShapeType, CSelectedShape &)> const & action)
{
	return m_createShapeCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSetRenderTargetForModel(std::function<void(ID2D1HwndRenderTarget*)> const & action)
{
	return m_setRenderTargetForModel.connect(action);
}
