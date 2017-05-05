#include "stdafx.h"
#include "ShapeCompositorView.h"

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


signal::Connection CShapeCompositorView::DoOnChangeRectCommand(std::function<void(const CFrame, size_t)> const & action)
{
	return m_createChangeRectCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnCreateShapeCommand(std::function<void(ShapeType)> const & action)
{
	return m_onCreateShape.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSetRenderTargetForModel(std::function<void(ID2D1HwndRenderTarget*)> const & action)
{
	return m_setRenderTargetForModel.connect(action);
}
