#pragma once

#include "AllShapes.h"
#include "../ShapeRenderer.h"

enum class TypeShape
{
		Triangle
	,	Rectangle
	,	Ellipse
};

class CShapeLayer;
class CShapeRender;
class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual void CreateShape(
		TypeShape type
		, const SShapeData & data
		, CShapeLayer & layer
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
		, CShapeLayer & layer
		, CShapeRender & shapeRenderer
	) const override;


	//--------------------------------------------
private:
	void BindPresenterWithModel(CShapeLayer & layer, CShapeRender & shapeRenderer) const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CCanvas * m_pCanvas = nullptr;
};