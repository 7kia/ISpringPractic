#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Shapes\ShapeFactory.h"

class CCanvas;
class CAddShapeCanvasCommand : public IMyCommand
{
public:
	CAddShapeCanvasCommand(
		CCanvas * pCanvas
		, ShapeType type
		, const CShapeFactory & factory
		, CSelectedShape & seletedShape
	);//ShapeType
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
	CCanvas * m_pCanvas = nullptr;
	const CShapeFactory * m_pFactory = nullptr;
	CSelectedShape * m_pSelectShape = nullptr;
};