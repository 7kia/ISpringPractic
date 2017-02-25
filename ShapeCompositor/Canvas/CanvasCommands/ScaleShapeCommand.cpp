#include "stdafx.h"
#include "ScaleShapeCommand.h"
#include "../SelectShape.h"

CScaleShapeCanvasCommand::CScaleShapeCanvasCommand(
	CShapePtr pShape
	, Vec2f shift
	, CSelectShape * pSelectedShape
)
	: m_pShape(pShape)
	, m_shift(shift)
	, m_pSelectedShape(pSelectedShape)
{
}

void CScaleShapeCanvasCommand::Execute()
{
	m_pShape->UpdateScale(m_shift);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->UpdateScaleFrame(m_shift);
	}
}

void CScaleShapeCanvasCommand::Cancel()
{
	m_pShape->UpdateScale(-m_shift);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->UpdateScaleFrame(-m_shift);
	}
}

