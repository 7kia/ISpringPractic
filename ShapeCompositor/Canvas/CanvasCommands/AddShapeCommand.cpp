#include "stdafx.h"
#include "AddShapeCommand.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(CCanvas * pCanvas, TypeShape type)
	: m_pCanvas(pCanvas)
	, m_type(type)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_pCanvas->AddShape(m_type);
}

void CAddShapeCanvasCommand::Cancel()
{
	m_pCanvas->DeleteLastShape();
}