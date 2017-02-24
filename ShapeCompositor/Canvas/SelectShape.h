#pragma once

#include <memory>

#include "Shapes\AllShapes.h"
#include "ShapeRenderer.h"
#include "Shapes\ShapeFactory.h"

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);

class CSelectShape
	: public IDrawable
{
public:
	CSelectShape(CD2DObjectRenderer & shapeRenderer, const CShapeFactory & shapeFactory);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePtr shape);
	CShapePtr				GetShape() const;
	void					ResetSelectShapePtr();
	//--------------------------------------------
	// IDrawable
	void					Accept(IShapeVisitor & renderer) const override;// TODO : must be = 0
	//--------------------------------------------
private:
	void					SetViewPosition();
	void					SetMoveView();
	void					SetResizeView();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SShapeData						m_frameData;
	CShapePtr						m_selectShape;

	std::vector<CShapePtr>				m_moveShape;
	std::vector<CShapePtr>				m_resizeShapes;
};