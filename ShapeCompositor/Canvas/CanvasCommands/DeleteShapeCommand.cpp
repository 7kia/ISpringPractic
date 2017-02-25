#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../Canvas.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(CCanvas *const pCanvas)
	: m_pCanvas(pCanvas)
	, m_data(pCanvas->GetSelectShape()->GetShapeData())
	, m_index(pCanvas->GetIndexSelectShape())
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	m_pCanvas->DeleteShape(m_index);
}

void CDeleteShapeCanvasCommand::Cancel()
{
	m_pCanvas->InsertShape(m_index, m_data);
}
