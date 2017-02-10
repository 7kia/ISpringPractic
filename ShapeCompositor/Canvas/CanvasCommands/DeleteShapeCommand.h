#pragma once

#include "CanvasCommand.h"
#include "../Canvas.h"
#include "../ShapeTypeDefiner.h"

class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		CCanvas * pCanvas
		, const CShapePresenterPtr shape
		, size_t index
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
	CShapeTypeDefiner m_typeDefinder;
	TypeShape m_type = TypeShape::Rectangle;
	SShapeData m_data;
	size_t m_index = 0;
	CCanvas * m_pCanvas = nullptr;
};