#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../Canvas.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(CCanvas *const pCanvas
	, const CShapePtr shape
	, size_t index
)
	: m_pCanvas(pCanvas)
	, m_data(shape->GetShapeData())
	, m_index(index)
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	m_pCanvas->DeleteShape(m_index);
}

void CDeleteShapeCanvasCommand::Cancel()
{

	if (m_index == 0)
	{
		m_pCanvas->InsertShape(m_type, 0, m_data);
	}
	else
	{
		m_pCanvas->InsertShape(m_type, m_index - 1, m_data);
	}
}
