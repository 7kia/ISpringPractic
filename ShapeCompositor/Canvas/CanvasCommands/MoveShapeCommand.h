#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectedShape;
class CMoveShapeCanvasCommand : public IMyCommand
{
public:
	CMoveShapeCanvasCommand(
		CShapePtr pShape
		, Vec2f shift
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
	Vec2f		m_shift;
};