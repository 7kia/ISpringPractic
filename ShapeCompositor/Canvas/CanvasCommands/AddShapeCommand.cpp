#include "stdafx.h"
#include "AddShapeCommand.h"
#include "../Canvas.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(
	CCanvas * pCanvas
	, ShapeType type
	, const CShapeFactory & factory
)
	: m_pCanvas(pCanvas)
	, m_type(type)
	, m_pFactory(&factory)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_pCanvas->PushBackShape(
		m_pFactory->CreateShape(
			SShapeData(
				m_type
				, Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)
			)
		)
	);
}

void CAddShapeCanvasCommand::Cancel()
{
	m_pCanvas->DeleteLastShape();
}