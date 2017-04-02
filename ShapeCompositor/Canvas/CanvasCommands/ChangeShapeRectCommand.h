#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectedShape;
class IGetShape;
class CChangeShapeRectCanvasCommand : public IMyCommand
{
public:
	CChangeShapeRectCanvasCommand(
		IGetShape * pShapeStorage
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
	IGetShape *	m_pCanvas = nullptr;
	size_t		m_index;
	CSelectedShape * m_pSelectedShape = nullptr;
	CFrame		m_oldFrame;
	CFrame		m_newData;
};