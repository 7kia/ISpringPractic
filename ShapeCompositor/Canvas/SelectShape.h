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
	void					SetShape(CShapePresenter * shape);
	CShapePresenterPtr		GetShape() const;
	void					ResetSelectShapePtr();
	void					Render();

	//--------------------------------------------

private:
	void					SetViewPosition();

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SPresenterData					m_frameData;
	CShapePresenter *				m_selectPresenter = nullptr;

	CShapeLayer						m_moveShape;
	CShapeLayer						m_resizeShape;
};