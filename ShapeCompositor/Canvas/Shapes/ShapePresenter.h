#pragma once

#include "Observer.h"
#include "CShape.h"

class CShapePresenter 
	: public CObservable<SPresenterData>// For update view and model
	, public IObserver<SPresenterData>// For update from CSelectShape
	, public IIsPointIntersection
{
public:
	CShapePresenter(const Vec2f position, const SSize size);

	~CShapePresenter();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void CheckPointIntersection(const Vec2f point);

	//--------------------------------------------
	// CObservable<SPresenterData>
	SPresenterData GetChangedData() const override;
	//--------------------------------------------
	//  IObserver<SPresenterData>
	void Update(const SPresenterData & data) override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Vec2f m_position;

	SSize m_size;
};

using CShapePresenterPtr = std::shared_ptr<CShapePresenter>;