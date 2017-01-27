#pragma once

#include "CanvasCommand.h"
#include "../Canvas.h"

class CAddShapeCanvasCommand : public CCanvasCommand
{
public:
	CAddShapeCanvasCommand(CCanvas * pCanvas, TypeShape type);//TypeShape
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// ICommand
	void Execute() override;
	void Cancel() override;

	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	TypeShape m_type;
};