#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CSelectShape;
class CMoveShapeCanvasCommand : public IMyCommand
{
public:
	CMoveShapeCanvasCommand(
		CShapePtr pShape
		, Vec2f shift
		, CSelectShape & selectedShape
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
	Vec2f		m_shift;
};