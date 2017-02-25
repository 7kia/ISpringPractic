#include "stdafx.h"
#include "MoveShapeCommand.h"
#include "../SelectShape.h"

CMoveShapeCanvasCommand::CMoveShapeCanvasCommand(
	CShapePtr pShape
	, Vec2f shift
	, CSelectShape * pSelectedShape
)
	: m_pShape(pShape)
	, m_shift(shift)
	, m_pSelectedShape(pSelectedShape)
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
