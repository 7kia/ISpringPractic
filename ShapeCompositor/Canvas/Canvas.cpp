#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
	: IMouseEventHandler()
	, m_shapeFactory(this)
	, m_selectShape(m_shapeRenderer, m_shapeFactory)
{
}



HRESULT CCanvas::Render()
{
	for (const auto & shape : m_shapes)
	{
		shape->Draw(m_shapeRenderer);
	}

	m_selectShape.Draw(m_shapeRenderer);

	return m_shapeRenderer.EndDraw();
}

HRESULT CCanvas::CreateRecources(CShapeCompositorView * window)
{
	return m_shapeRenderer.CreateRecources(window);
}

void CCanvas::ClearRecources()
{
	m_shapeRenderer.ClearRecources();
}

void CCanvas::AddShape(TypeShape type, SShapeData data)
{
	m_shapeFactory.CreateShape(
		type
		, data
		, m_shapes
		, m_shapeRenderer
	);
}

void CCanvas::DeleteShape(size_t index)
{
	m_shapes.erase(m_shapes.begin() + index);
}

void CCanvas::DeleteShape(CShapePtr pShape)
{
	size_t index = GetIndexShape(pShape);
	if (index != size_t(-1))
	{
		DeleteShape(index);
	}
}

void CCanvas::DeleteLastShape()
{
	if (IsSelectLast())
	{
		m_selectShape.ResetSelectShapePtr();
	}

	DeleteShape(m_shapes.size() - 1);
}

void CCanvas::ChangeSelectShape(const Vec2f mousePosition)
{
	auto selectShape = GetShape(Vec2f(float(mousePosition.x), float(mousePosition.y)));

	if (!selectShape._Expired())
	{
		m_selectShape.SetShape(selectShape);
	}
	else
	{
		m_selectShape.ResetSelectShapePtr();
	}
}

CShapePtr CCanvas::GetShape(const Vec2f mousePosition)
{
	CShapePtr foundShape;
	for (auto iter = m_shapes.rbegin(); iter != m_shapes.rend(); ++iter)
	{
		if ((*iter)->IsPointIntersection(mousePosition))
		{
			foundShape = *iter;
			break;
		}
	}
	return foundShape;
}

CShapePtr CCanvas::GetSelectShape()
{
	return m_selectShape.GetShape();
}

const CShapePtr CCanvas::GetSelectShape() const
{
	return m_selectShape.GetShape();
}

size_t CCanvas::GetIndexSelectShape() const
{
	return GetIndexShape(GetSelectShape());
}

bool CCanvas::IsSelectLast() const
{
	return m_selectShape.GetShape() == m_shapes.back();
}

size_t CCanvas::GetIndexShape(CShapePtr pShape) const 
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}

void CCanvas::DeleteSelectShape()
{
	//m_pCanvas->DeleteShape(m_pCanvas->GetSelectShape());
	CanvasCommandPtr createCommand = std::make_shared<CDeleteShapeCanvasCommand>(
		this
		, GetSelectShape()
		, GetIndexSelectShape()
		);
	//AddCommand(createCommand);
	//ExecuteCurrent();

}

void CCanvas::HandleLButtHandleDown(CPoint point)
{
	ChangeSelectShape(Vec2f(float(point.x), float(point.y)));
}

void CCanvas::HandleLButtHandleUp(CPoint point)
{
	// TODO
}

void CCanvas::HandleRButtHandleUp(CPoint point)
{
	// TODO
}

void CCanvas::HandleMouseMove(CPoint point)
{
	//m_pCanvas->ChangeSelectShape(Vec2f(float(point.x), float(point.y)));
}


