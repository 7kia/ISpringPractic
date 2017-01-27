#pragma once

#include "../Canvas.h"

class IMyCommand
{
public:
	virtual ~IMyCommand() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void Execute() = 0;
	virtual void Cancel() = 0;
};

class CCanvasCommand : public IMyCommand
{
public:
	CCanvasCommand();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// ICommand

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	CCanvas * m_pCanvas;
};
