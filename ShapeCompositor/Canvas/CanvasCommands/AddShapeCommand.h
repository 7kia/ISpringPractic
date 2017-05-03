#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Shapes\ShapeViewFactory.h"

class IShapeCollection;
class CAddShapeCanvasCommand : public IMyCommand
{
public:
	CAddShapeCanvasCommand(
		IShapeCollection & pCanvas
		, ShapeType type
		, const CShapeViewFactory & factory
		, CSelectedShape & seletedShape
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IMyCommand
	void Execute() override;
	void Cancel() override;
	void Destroy() override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ShapeType m_type = ShapeType::Rectangle;
	IShapeCollection & m_canvas;
	const CShapeViewFactory & m_factory;
	CSelectedShape & m_selectShape;
};