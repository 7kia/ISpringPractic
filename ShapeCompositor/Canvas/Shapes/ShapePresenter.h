#pragma once

#include "Observer.h"
#include "CShapeModel.h"

class CShapePresenter 
	: public CObservable<SShapeData>// For update view and model
	, public IObserver<SShapeData>
	, public IIsPointIntersection
	, public CShapeData
{
public:
	CShapePresenter(const Vec2f position, const SSize size);

	~CShapePresenter();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool CheckPointIntersection(const Vec2f point);

	//--------------------------------------------
	// CObservable<SPresenterData>
	SShapeData GetChangedData() const override;
	//--------------------------------------------

	void Update(const SShapeData & data) override;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};

using CShapePresenterPtr = std::shared_ptr<CShapePresenter>;
using CShapePresenterWeakPtr = std::weak_ptr<CShapePresenter>;