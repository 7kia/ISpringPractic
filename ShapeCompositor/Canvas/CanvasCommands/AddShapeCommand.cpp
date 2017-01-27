#include "stdafx.h"
#include "AddShapeCommand.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(TypeShape type)
	: CCanvasCommand()
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