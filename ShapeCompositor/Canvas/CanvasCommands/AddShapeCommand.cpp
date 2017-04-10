#include "stdafx.h"
#include "AddShapeCommand.h"
#include "../Canvas.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(
	IShapeCollection & pCanvas
	, ShapeType type
	, const CShapeFactory & factory
	, CSelectedShape & seletedShape
)
	: m_canvas(pCanvas)
	, m_type(type)
	, m_factory(factory)
	, m_selectShape(seletedShape)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_canvas.PushBackShape(
		m_factory.CreateShape(
			SShapeData(
				m_type
				, Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)
			)
		)
	);
}

void CAddShapeCanvasCommand::Cancel()
{
	if (m_canvas.IsSelectShape(m_canvas.GetAmountShapes() - 1, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	DeleteLastElement(m_canvas.GetShapes());
}