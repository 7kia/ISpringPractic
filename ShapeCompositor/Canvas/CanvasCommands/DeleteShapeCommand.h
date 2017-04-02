#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"

class IAddAndDeleteShape;
class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		IAddAndDeleteShape * pCanvas
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
	IAddAndDeleteShape * m_pCanvas = nullptr;
	CSelectedShape * m_pSelectShape = nullptr;
	const CShapeFactory * m_pFactory = nullptr;
};