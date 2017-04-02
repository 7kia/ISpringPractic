#include "stdafx.h"
#include "MoveShapeCommand.h"
#include "../SelectedShape.h"

CMoveShapeCanvasCommand::CMoveShapeCanvasCommand(
	CShapePtr pShape
	, const Vec2f & shift
	, CSelectedShape & selectedShape
)
	: m_pShape(pShape)
	, m_shift(shift)
	, m_pSelectedShape(&selectedShape)
{
}

void CMoveShapeCanvasCommand::Execute()
{
	m_pShape->Move(m_shift);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->MoveFrame(m_shift);
	}
}

void CMoveShapeCanvasCommand::Cancel()
{
	m_pShape->Move(-m_shift);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->MoveFrame(-m_shift);
	}
}
