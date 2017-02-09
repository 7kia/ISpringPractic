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
#include "ShapeLayer.h"

static const size_t MAX_COMMANDS = 5;

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
	void		AddShape(TypeShape type);
	void		DeleteShape(CShapePresenterPtr pShape);
	void		DeleteLastShape();

	CShapePresenterPtr GetShapePresenter(const Vec2f mousePosition);
private:

	HRESULT		RenderShapes();

	//////////////////////////////////////////////////////////////////////
	// Data
public:
	CShapeFactory								m_shapeFactory;
	CShapeRender								m_shapeRenderer;

	// TODO : see might require do private
	CShapeLayer									m_shapeLayer;
private:
};
