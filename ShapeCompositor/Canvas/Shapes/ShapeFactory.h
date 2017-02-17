#pragma once

#include "AllShapes.h"
#include "../ShapeRenderer.h"

#include <vector>

enum class TypeShape
{
		Triangle
	,	Rectangle
	,	Ellipse
};

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual void CreateShape(
		TypeShape type
		, const SShapeData & data
		, std::vector<CShapePtr> & sh
		, CShapeRender & shapeRenderer
	) const = 0;

};

class CCanvas;// For bind signals
class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory(CCanvas * pCanvas);
	friend CCanvas;// TODO : check correctness
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShapeFactory

	void CreateShape(
		TypeShape type
		, const SShapeData & data
		, std::vector<CShapePtr> & shapes
		, CShapeRender & shapeRenderer
	) const override;


	//--------------------------------------------
private:
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CCanvas * m_pCanvas = nullptr;
};