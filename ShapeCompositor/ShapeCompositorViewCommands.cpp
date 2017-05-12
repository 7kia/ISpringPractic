#include "stdafx.h"
#include "ShapeCompositorView.h"

signal::Connection CShapeCompositorView::DoOnSaveAsDocument(std::function<bool()> const & action)
{
	return m_onSaveAsDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSaveDocument(std::function<bool()> const & action)
{
	return m_onSaveDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnOpenDocument(std::function<bool()> const & action)
{
	return m_onOpenDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnNewDocument(std::function<bool()> const & action)
{
	return m_onNewDocument.connect(action);
}

signal::Connection CShapeCompositorView::DoOnUndoCommand(std::function<void()> const & action)
{
	return m_onUndoCommand.connect(action);
}

signal::Connection CShapeCompositorView::DoOnRedoCommand(std::function<void()> const & action)
{
	return m_onRedoCommand.connect(action);
}


signal::Connection CShapeCompositorView::DoOnDeleteShapeCommand(std::function<void(size_t)> const & action)
{
	return m_onDeleteShape.connect(action);
}

signal::Connection CShapeCompositorView::DoOnChangeRectCommand(std::function<void(const CFrame, const CFrame, size_t)> const & action)
{
	return m_onChangeRectShape.connect(action);
}

signal::Connection CShapeCompositorView::DoOnCreateShapeCommand(std::function<void(ShapeType)> const & action)
{
	return m_onCreateShape.connect(action);
}

signal::Connection CShapeCompositorView::DoOnSetRenderTargetForModel(std::function<void(ID2D1HwndRenderTarget*)> const & action)
{
	return m_onSetRenderTargetForModel.connect(action);
}
