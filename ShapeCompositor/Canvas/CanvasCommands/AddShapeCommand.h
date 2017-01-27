#pragma once

#include "CanvasCommand.h"

class CAddShapeCanvasCommand : public CCanvasCommand
{
public:
	CAddShapeCanvasCommand(TypeShape type);
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