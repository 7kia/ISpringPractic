#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
	: IMouseEventHandler()
	, m_selectShape(m_objectRenderer, m_shapeFactory)
{
}



HRESULT CCanvas::Draw()
{
	for (const auto & shape : *m_pShapes)
	{
		m_objectRenderer.Draw(*shape);
	}

	m_objectRenderer.Draw(m_selectShape);

	return m_objectRenderer.EndDraw();
}

HRESULT CCanvas::CreateRecources(CShapeCompositorView * window)
{
	return m_objectRenderer.CreateRecources(window);
}

void CCanvas::ClearRecources()
{
	m_objectRenderer.ClearRecources();
}

bool CCanvas::DoneUpdateSelectedShape() const
{
	return m_selectShape.HaveSelectedShape() 
		&& !m_selectShape.IsUpdate() 
		&& (m_selectShape.GetShift() != Vec2f());
}

Vec2f CCanvas::GetShiftSelectedShape() const
{
	return m_selectShape.GetShift();
}

CSelectShape * CCanvas::GetFrameSelectedShape()
{
	return &m_selectShape;
}

CSelectShape::UpdateType CCanvas::GetUpdateStateSelectedShape() const
{
	return m_selectShape.GetUpdateType();
}

void CCanvas::PushBackShape(SShapeData data)
{
	m_pShapes->push_back(
		m_shapeFactory.CreateShape(data, m_objectRenderer)
	);
}

void CCanvas::InsertShape(size_t insertIndex, SShapeData data)
{
	if (!IsBetween(insertIndex, size_t(0), m_pShapes->size()))
	{
		throw std::runtime_error("Index out range");
	}

	m_pShapes->insert(
		m_pShapes->begin() + insertIndex
		, m_shapeFactory.CreateShape(data, m_objectRenderer)	
	);
}

std::vector<CShapePtr>* CCanvas::GetShapes() const
{
	return m_pShapes;
}

void CCanvas::SetDocument(CShapeCompositorDoc * document)
{
	m_pDocument = document;
	m_pShapes = &m_pDocument->GetShapes();
}

void CCanvas::DeleteShape(size_t index)
{
	if (IsSelectShape(index))
	{
		m_selectShape.ResetSelectShapePtr();
	}

	m_pShapes->erase(m_pShapes->begin() + index);
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
	DeleteShape(m_pShapes->size() - 1);
}

void CCanvas::ChangeSelectShape(const Vec2f mousePosition)
{
	auto selectShape = GetShape(Vec2f(float(mousePosition.x), float(mousePosition.y)));

	if (selectShape.get() != nullptr)
	{
		if (m_selectShape.GetShape() != selectShape)
		{
			m_selectShape.SetShape(selectShape);
		}
	}
	else
	{
		m_selectShape.ResetSelectShapePtr();
	}
}

CShapePtr CCanvas::GetShape(const Vec2f mousePosition)
{
	CShapePtr foundShape;
	for (auto iter = m_pShapes->rbegin(); iter != m_pShapes->rend(); ++iter)
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

bool CCanvas::IsSelectShape(size_t index) const
{
	return m_selectShape.GetShape() == (*m_pShapes)[index];
}

size_t CCanvas::GetIndexShape(CShapePtr pShape) const 
{
	return  std::find(m_pShapes->begin(), m_pShapes->end(), pShape) - m_pShapes->begin();
}

bool CCanvas::HandleLButtHandleDown(CPoint point)
{

	if (m_selectShape.HaveSelectedShape())
	{
		if (m_selectShape.IsResize(Vec2f(float(point.x), float(point.y))))
		{
			m_selectShape.SetUpdateState(true);
			return true;
		}
	}	
	ChangeSelectShape(Vec2f(float(point.x), float(point.y)));

	if (m_selectShape.HaveSelectedShape())
	{
		if (m_selectShape.IsMove(Vec2f(float(point.x), float(point.y))))
		{
			m_selectShape.SetUpdateState(true);
			return true;
		}
	}
	return false;
}

bool CCanvas::HandleLButtHandleUp(CPoint point)
{
	if (m_selectShape.HaveSelectedShape())
	{
		m_selectShape.SetUpdateState(false);
		return true;
	}
	return false;
}

bool CCanvas::HandleRButtHandleUp(CPoint point)
{
	// TODO
	return false;
}

bool CCanvas::HandleMouseMove(CPoint point)
{
	if (m_selectShape.HaveSelectedShape() && m_selectShape.IsUpdate())
	{
		m_selectShape.HandleMoveMouse(Vec2f(float(point.x), float(point.y)));
		return true;
	}
	return false;
}


