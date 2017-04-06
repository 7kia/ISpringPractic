#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Shapes\ShapeFactory.h"

class IShapeCollection;
class CAddShapeCanvasCommand : public IMyCommand
{
public:
	CAddShapeCanvasCommand(
		IShapeCollection & pCanvas
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
	IShapeCollection & m_pCanvas;
	const CShapeFactory * m_pFactory = nullptr;
	CSelectedShape * m_pSelectShape = nullptr;
};