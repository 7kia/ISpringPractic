#include "stdafx.h"
#include "AddShapeCommand.h"
#include "../Canvas.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(
	IShapeCollection & pCanvas
	, ShapeType type
	, const CShapeFactory & factory
	, CSelectedShape & seletedShape
)
	: m_pCanvas(pCanvas)
	, m_type(type)
	, m_pFactory(&factory)
	, m_pSelectShape(&seletedShape)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_pCanvas.PushBackShape(
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
	if (m_pCanvas.IsSelectShape(m_pCanvas.GetAmountShapes() - 1, m_pSelectShape->GetShape()))
	{
		m_pSelectShape->ResetSelectShapePtr();
	}
	DeleteLastElement(m_pCanvas.GetShapes());
}