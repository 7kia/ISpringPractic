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

static const size_t MAX_COMMANDS = 5;

static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView;
class CCanvasController;


class CCanvas
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

	HRESULT		Render();
	void		AddShape(TypeShape type, SShapeData data = SShapeData(Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)));
	void		DeleteShape(size_t index);
	void		DeleteShape(CShapePtr pShape);// TODO : see need it variant
	void		DeleteLastShape();

	void				ChangeSelectShape(const Vec2f mousePosition);
	CShapePtr			GetShape(const Vec2f mousePosition);// TODO : see need private
	CShapePtr			GetSelectShape();
	const CShapePtr		GetSelectShape() const;
	size_t				GetIndexSelectShape() const;
private:

	bool		IsSelectLast() const;

	size_t		GetIndexShape(CShapePtr pShape) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	CShapeFactory								m_shapeFactory;
	CShapeRender								m_shapeRenderer;

	CSelectShape								m_selectShape;
	// TODO : see might require do private
	std::vector<CShapePtr>						m_shapes;
private:
};
