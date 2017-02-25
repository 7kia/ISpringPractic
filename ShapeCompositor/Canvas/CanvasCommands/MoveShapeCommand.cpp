#include "stdafx.h"
#include "MoveShapeCommand.h"
#include "../Canvas.h"

CMoveShapeCanvasCommand::CMoveShapeCanvasCommand(CShapePtr pShape, Vec2f shift)
	: m_pShape(pShape)
	, m_shift(shift)
{
}

void CMoveShapeCanvasCommand::Execute()
{
	m_pShape->Move(m_shift);
}

void CMoveShapeCanvasCommand::Cancel()
{
	m_pShape->Move(-m_shift);
}
