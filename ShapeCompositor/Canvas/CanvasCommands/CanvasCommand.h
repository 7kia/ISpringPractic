#pragma once

#include <memory>
//#include "../Canvas.h"

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

class CCanvas;

class CCanvasCommand : public IMyCommand
{
public:
	CCanvasCommand(CCanvas * pCanvas);
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
