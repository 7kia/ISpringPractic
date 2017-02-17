#pragma once

#include <memory>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <afxwin.h>

#include <vector>

#include "Shapes\ShapeFactory.h"
#include "ShapeRenderer.h"
#include "SelectShape.h"
#include "CanvasCommands\AllCanvasCommand.h"
#include "MouseEventHandler.h"


static const size_t MAX_COMMANDS = 5;

static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView;
class CCanvasController;


class CCanvas
	: public IMouseEventHandler
{
public:
	CCanvas();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	// The function must call before use canvas
	HRESULT		CreateRecources(CShapeCompositorView * window);
	void		ClearRecources();
	//

	// Commands
	void AddTriangle();
	void AddRectangle();
	void AddEllipse();
	void Undo();
	void Redo();

	void DeleteSelectShape();
	//

	//--------------------------------------------
	// IMouseEventHandler

	void HandleLButtHandleDown(CPoint point) override;
	void HandleLButtHandleUp(CPoint point) override;
	void HandleRButtHandleUp(CPoint point) override;
	void HandleMouseMove(CPoint point) override;

	//--------------------------------------------

	HRESULT		Render();
	void		DeleteShape(size_t index);
	void		DeleteShape(CShapePtr pShape);// TODO : see need it variant
	void		DeleteLastShape();

	void				ChangeSelectShape(const Vec2f mousePosition);
	CShapePtr			GetShape(const Vec2f mousePosition);// TODO : see need private
	CShapePtr			GetSelectShape();
	const CShapePtr		GetSelectShape() const;
	size_t				GetIndexSelectShape() const;

	void		AddShape(TypeShape type, SShapeData data = SShapeData(Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)));

private:

	//
	void AddCommand(const CanvasCommandPtr command);
	void ExecuteCurrent();
	void UndoCommand();
	void RedoCommand();
	//

	bool		IsSelectLast() const;

	size_t		GetIndexShape(CShapePtr pShape) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	CShapeFactory								m_shapeFactory;
	CShapeRender								m_shapeRenderer;

	CSelectShape								m_selectShape;

	std::vector<CanvasCommandPtr>						m_history;
	std::vector<CanvasCommandPtr>::reverse_iterator		m_currentCommand = m_history.rbegin();

	// TODO : see might require do private
	std::vector<CShapePtr>						m_shapes;
private:
};
