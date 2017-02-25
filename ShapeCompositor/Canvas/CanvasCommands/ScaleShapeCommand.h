#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectShape;
class CScaleShapeCanvasCommand : public IMyCommand
{
public:
	CScaleShapeCanvasCommand(
		CShapePtr pShape
		, SFrameData oldData
		, SFrameData newData
		, CSelectShape * pSelectedShape
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
	CSelectShape * m_pSelectedShape = nullptr;
	SFrameData		m_oldData;
	SFrameData		m_newData;
};