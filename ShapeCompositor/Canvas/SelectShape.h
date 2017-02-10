#pragma once

#include <memory>

#include "Shapes\AllShapes.h"
#include "ShapeRenderer.h"
#include "Shapes\ShapeFactory.h"
#include "ShapeLayer.h"

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);

class CSelectShape
{
public:
	CSelectShape(CShapeRender & shapeRenderer, const CShapeFactory & shapeFactory);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePresenterPtr shape);
	CShapePresenterPtr		GetShape() const;
	void					ResetSelectShapePtr();
	void					Render();

	//--------------------------------------------

private:
	void					SetViewPosition();
	void					SetMoveView();
	void					SetResizeView();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SShapeData						m_frameData;
	CShapePresenterPtr				m_selectPresenter;

	CShapeLayer						m_moveShape;
	CShapeLayer						m_resizeShape;
};