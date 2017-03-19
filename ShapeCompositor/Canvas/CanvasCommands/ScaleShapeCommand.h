#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectedShape;
class CScaleShapeCanvasCommand : public IMyCommand
{
public:
	CScaleShapeCanvasCommand(
		CShapePtr pShape
		, SFrameData oldData
		, SFrameData newData
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
	SFrameData		m_oldData;
	SFrameData		m_newData;
};