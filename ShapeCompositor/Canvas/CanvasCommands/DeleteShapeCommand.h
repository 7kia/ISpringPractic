#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"

class IShapeCollection;
class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		IShapeCollection & pCanvas,
		CSelectedShape & selectedShape,
		const CShapeViewFactory & factory
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
	CShapeModel m_data;
	size_t m_index = 0;
	IShapeCollection & m_canvas;
	CSelectedShape & m_selectShape;
	const CShapeViewFactory & m_factory;
};