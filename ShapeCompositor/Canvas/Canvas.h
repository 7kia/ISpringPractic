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

	// For drag and drop
	bool		DoneUpdateSelectedShape() const;
	Vec2f		GetShiftSelectedShape() const;
	CSelectShape * GetFrameSelectedShape();
	CSelectShape::UpdateType	GetUpdateStateSelectedShape() const;
	//

	//--------------------------------------------
	// IMouseEventHandler

	void HandleLButtHandleDown(CPoint point) override;
	void HandleLButtHandleUp(CPoint point) override;
	void HandleRButtHandleUp(CPoint point) override;
	void HandleMouseMove(CPoint point) override;

	//--------------------------------------------

	HRESULT		Draw();
	void		DeleteShape(size_t index);
	void		DeleteShape(CShapePtr pShape);// TODO : see need it variant
	void		DeleteLastShape();

	void				ChangeSelectShape(const Vec2f mousePosition);
	CShapePtr			GetShape(const Vec2f mousePosition);// TODO : see need private
	CShapePtr			GetSelectShape();
	const CShapePtr		GetSelectShape() const;// TODO : see need it
	size_t				GetIndexSelectShape() const;

	void PushBackShape(SShapeData data);
	void InsertShape(size_t insertIndex, SShapeData data);

private:

	bool		IsSelectShape(size_t index) const;

	size_t		GetIndexShape(CShapePtr pShape) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	CShapeFactory								m_shapeFactory;
	CD2DObjectRenderer							m_objectRenderer;// TODO : transfer to CShapeCompositiorView, fix Draw

	CSelectShape								m_selectShape;

	// TODO : see might require do private
	std::vector<CShapePtr>						m_shapes;
private:
};
