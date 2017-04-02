#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectedShape;
class CScaleShapeCanvasCommand : public IMyCommand
{
public:
	CScaleShapeCanvasCommand(
		CShapePtr pShape
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
	CShapePtr	m_pShape;
	CSelectedShape * m_pSelectedShape = nullptr;
	CFrame		m_oldData;
	CFrame		m_newData;
};