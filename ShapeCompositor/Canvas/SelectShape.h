#pragma once

#include <memory>

#include "Shapes\AllShapes.h"

class CSelectShape
	: public CObservable<SPresenterData>
{
public:
	CSelectShape();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePresenterPtr shape);
	CShapePresenterPtr		GetShape() const;

	//--------------------------------------------
	// NameInterface
	SPresenterData			GetChangedData() const override;
	//--------------------------------------------


	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SPresenterData					m_frameData;
	std::weak_ptr<CShapePresenter>	m_selectPresenter;
};