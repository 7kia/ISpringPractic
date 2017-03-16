#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
	: IMouseEventHandler()
	, IDrawable()
	, CFrame(Vec2f(), SSize(640.f, 480.f))
	, m_selectShape(m_shapeFactory)
{
}

void CCanvas::Accept(IObjectVisitor & renderer) const
{
	renderer.Visit(*this);
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

const CSelectShape * CCanvas::GetFrameSelectedShape() const
{
	return &m_selectShape;
}

CSelectShape::UpdateType CCanvas::GetUpdateStateSelectedShape() const
{
	return m_selectShape.GetUpdateType();
}

void CCanvas::PushBackShape(SShapeData data)
{
	m_shapes.push_back(
		m_shapeFactory.CreateShape(data)
	);
}

void CCanvas::InsertShape(size_t insertIndex, SShapeData data)
{
	if (!IsBetween(insertIndex, size_t(0), m_shapes.size()))
	{
		throw std::runtime_error("Index out range");
	}

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, m_shapeFactory.CreateShape(data)	
	);
}

std::vector<CShapePtr> CCanvas::GetShapes() const
{
	return m_shapes;
}

void CCanvas::SetShapes(const std::vector<SShapeData> & shapesData)
{
	m_shapes.clear();
	for (const auto & data : shapesData)
	{
		PushBackShape(data);
	}
}

void CCanvas::SetDocument(CShapeCompositorDoc * document)
{
	m_pDocument = document;
}

void CCanvas::DeleteShape(size_t index)
{
	if (IsSelectShape(index))
	{
		m_selectShape.ResetSelectShapePtr();
	}

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
	DeleteShape(m_shapes.size() - 1);
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

bool CCanvas::IsSelectShape(size_t index) const
{
	return m_selectShape.GetShape() == m_shapes[index];
}

size_t CCanvas::GetIndexShape(CShapePtr pShape) const 
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
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


