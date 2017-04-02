#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectedShape;
class CCanvas;
class CChangeShapeRectCanvasCommand : public IMyCommand
{
public:
	CChangeShapeRectCanvasCommand(
		CCanvas * pCanvas
		, const CFrame & oldData
		, const CFrame & newData
		, CSelectedShape & selectedShape
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
	CCanvas *	m_pCanvas = nullptr;
	size_t		m_index;
	CSelectedShape * m_pSelectedShape = nullptr;
	CFrame		m_oldFrame;
	CFrame		m_newData;
};