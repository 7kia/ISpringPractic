#pragma once

#include "AllShapes.h"

enum class TypeShape
{
		Triangle
	,	Rectangle
	,	Ellipse
};

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_OUTLINE_COLOR = Color(0.75f, 0.75f, 0.75f);
static const Color DEFAULT_FILL_COLOR = Color(0.45f, 0.15f, 0.55f);

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