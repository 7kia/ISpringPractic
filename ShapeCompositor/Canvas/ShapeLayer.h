#pragma once

#include "Shapes\ShapeFactory.h"
#include "ShapeRenderer.h"

class CShapeLayer
{
public:
	CShapeLayer();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//void					SetShapeData();
	void								PushBackShapeData(CShapeDataPtr data);
	void								InsertBackShapeData(CShapeDataPtr data, size_t index);// For delete command
	CShapeDataPtr						GetShapeData(size_t index);// TODO : add consts
	CShapeDataPtr						GetBackShapeData() const;

	void								PushBackShapePreseneter(CShapePresenterPtr data);
	void								InsertBackShapeData(CShapePresenterPtr data, size_t index);// For delete command
	CShapePresenterPtr					GetShapePreseneter(size_t index);
	CShapePresenterPtr					GetShapePreseneter(Vec2f position);
	CShapePresenterPtr					GetBackShapePreseneter() const;

	std::vector<CShapeDataPtr> &		GetShapesData();
	std::vector<CShapePresenterPtr> &	GetShapePresenters();

	void		DeleteShape(CShapePresenterPtr pShape);
	void		DeleteLastShape();

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<CShapeDataPtr>					m_shapesData;
	std::vector<CShapePresenterPtr>				m_shapePresenters;

};