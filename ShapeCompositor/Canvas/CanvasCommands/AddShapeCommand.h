#pragma once

#include "CanvasCommand.h"
#include "../Canvas.h"

class CAddShapeCanvasCommand : public IMyCommand
{
public:
	CAddShapeCanvasCommand(CCanvas * pCanvas, TypeShape type);//TypeShape
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
	TypeShape m_type;
	CCanvas * m_pCanvas;
};