#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"

class CCanvas;
class CMoveShapeCanvasCommand : public IMyCommand
{
public:
	CMoveShapeCanvasCommand(CShapePtr pShape, Vec2f shift);
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
	TypeShape	m_type = TypeShape::Rectangle;
	CCanvas *	m_pCanvas = nullptr;
	CShapePtr	m_pShape;
	Vec2f		m_shift;
};