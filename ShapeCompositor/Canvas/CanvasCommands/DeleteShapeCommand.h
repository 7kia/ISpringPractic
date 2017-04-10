#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"

class IShapeCollection;
class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		IShapeCollection & pCanvas
		, CSelectedShape & seletedShape
		, const CShapeFactory & factory
	);
//////////////////////////////////////////////////////////////////////
// Methods
public:
	//--------------------------------------------
	// IMyCommand
	void Execute() override;
	void Cancel() override;

	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ShapeType m_type = ShapeType::Rectangle;
	SShapeData m_data;
	size_t m_index = 0;
	IShapeCollection & m_canvas;
	CSelectedShape & m_selectShape;
	const CShapeFactory & m_factory;
};