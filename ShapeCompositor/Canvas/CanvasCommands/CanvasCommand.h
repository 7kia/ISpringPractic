#pragma once

#include "../Canvas.h"

class ICommand
{
public:
	virtual ~ICommand() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void Execute() = 0;
	virtual void Cancel() = 0;
};

class CCanvasCommand : public ICommand
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

