#include "stdafx.h"
#include "ShapePresenter.h"

CShapePresenter::CShapePresenter(const Vec2f position, const SSize size)
	: CObservable<SShapeData>()// For update view and model
	, IObserver<SShapeData>()
	, IIsPointIntersection()
	, CShapeData(position, size)
{
}

CShapePresenter::~CShapePresenter()
{
}

bool CShapePresenter::CheckPointIntersection(const Vec2f point)
{
	bool result = IsPointIntersection(point);
	if (result)
	{
		NotifyObservers();// TODO : check need it there
	}
	return result;
}

SShapeData CShapePresenter::GetChangedData() const
{
	SShapeData info;
	info.position = m_position;
	info.size = m_size;
	info.fillColor = m_fillColor;
	info.outlineColor = m_outlineColor;

	return info;
}

void CShapePresenter::Update(const SShapeData & data)
{
	m_position = data.position;
	m_size = data.size;
	m_fillColor = data.fillColor;
	m_outlineColor = data.outlineColor;

	NotifyObservers();
}
