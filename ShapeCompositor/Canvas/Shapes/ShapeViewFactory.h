#pragma once

#include "AllShapes.h"
#include "Picture/PictureView.h"
#include <vector>

class CShapeViewFactory
{
public:
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	static CShapeViewPtr CreateShape(const CShapeModel & data);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};