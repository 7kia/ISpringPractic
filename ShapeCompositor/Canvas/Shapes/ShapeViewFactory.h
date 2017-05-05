#pragma once

#include "AllViewShapes.h"
#include "Picture/PictureView.h"
#include "Picture/PictureModel.h"
#include <vector>

class CShapeViewFactory
{
public:
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	CShapeViewPtr CreateShape(CShapeModelPtr & data);
		//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::shared_ptr<CPictureView> GetPictureView(CShapeModelPtr & data);
};