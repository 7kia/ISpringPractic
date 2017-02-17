#include "stdafx.h"
#include "AddShapeCommand.h"
#include "../Canvas.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(CCanvas * pCanvas, TypeShape type)
	: m_pCanvas(pCanvas)
	, m_type(type)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_pCanvas->PushBackShape(SShapeData(m_type, Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)));
}

void CAddShapeCanvasCommand::Cancel()
{
	m_pCanvas->DeleteLastShape();
}