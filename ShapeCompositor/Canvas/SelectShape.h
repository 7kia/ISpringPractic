#pragma once

#include <memory>

#include "Shapes\AllShapes.h"
#include "ShapeRenderer.h"
#include "Shapes\ShapeFactory.h"
#include "ShapeLayer.h"

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);

class CSelectShape
	: public CObservable<SPresenterData>
{
public:
	CSelectShape(CShapeRender & shapeRenderer, const CShapeFactory & shapeFactory);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePresenterPtr shape);
	CShapePresenterPtr		GetShape() const;

	//--------------------------------------------
	// NameInterface
	SPresenterData			GetChangedData() const override;
	//--------------------------------------------
	void					Render();
private:
	void					SetViewPosition();

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SPresenterData					m_frameData;
	std::weak_ptr<CShapePresenter>	m_selectPresenter;

	CShapeLayer						m_frameLayer;
};