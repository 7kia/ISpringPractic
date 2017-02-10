#pragma once

#include "CanvasCommand.h"
#include "../Canvas.h"

class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		CCanvas * pCanvas
		, CShapePresenterPtr shape
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
	TypeShape m_type = TypeShape::Rectangle;
	SShapeData m_data;
	size_t m_index = 0;
	CCanvas * m_pCanvas = nullptr;
};