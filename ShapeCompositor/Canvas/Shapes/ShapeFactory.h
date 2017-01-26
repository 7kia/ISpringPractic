#pragma once

#include "AllShapes.h"

enum class TypeShape
{
		Triangle
	,	Rectangle
	,	Circle
};

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_COLOR = Color(0.25f, 0.25f, 0.25f);

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;

	virtual PCShape CreateShape(TypeShape type, const Vec2f position) = 0;
};

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShapeFactory

	PCShape CreateShape(TypeShape type, const Vec2f position) override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};