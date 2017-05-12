#include "stdafx.h"
#include "CanvasView.h"
#include "GlobalFunctions.h"

CCanvasView::CCanvasView()
{
	CShapeViewFactory factory;
	m_canvasBorder = factory.CreateShape(
		std::make_shared<CShapeModel>(
			ShapeType::Rectangle,
			Vec2f(
				CanvasNamespace::CANVAS_SIZE.width / 2.f,
				CanvasNamespace::CANVAS_SIZE.height / 2.f
			),
			CanvasNamespace::CANVAS_SIZE,
			NOT_COLOR,
			BLACK_COLOR,
			3.f
		)
	);
}

void CCanvasView::Draw(IShapeRenderer & renderer)
{
	renderer.Draw(*m_canvasBorder.get());

	for (const auto & shape : m_shapeViews)
	{
		renderer.Draw(*shape);
	}

	if (m_selectedShape.HaveSelectedShape())
	{
		renderer.Draw(*m_selectedShape.GetFrameShape());
		for (const auto & shape : m_selectedShape.GetDragPoints())
		{
			renderer.Draw(*shape);
		}
	}
}

CFrame CCanvasView::GetOldFrameSelectedShape() const
{
	return m_oldFrame;
}

size_t CCanvasView::GetIndexSelectedShape() const
{
	if (!m_selectedShape.HaveSelectedShape())
	{
		throw std::runtime_error("No selected shape");
	}
	return GetShapeIndex(m_selectedShape.GetShape());
}

bool CCanvasView::HaveSelectedShape() const
{
	return m_selectedShape.HaveSelectedShape();
}

void CCanvasView::ResetSelectedShapeUpdateParameters()
{
	m_selectedShape.ResetUpdateParameters();// TODO : rename functions(both reset)
}

CFrame CCanvasView::GetFrameSelectedShape() const
{
	return m_selectedShape.GetFrame();
}

void CCanvasView::AddShapeView(const CShapeViewPtr & pView, size_t insertIndex)
{
	CheckIndex(insertIndex, m_shapeViews.size());
	m_shapeViews.insert(m_shapeViews.begin() + insertIndex, pView);
}

void CCanvasView::DeleteShapeView(size_t index)
{
	CheckIndex(index, m_shapeViews.size() - 1);
	if (m_selectedShape.GetShape() == m_shapeViews[index])
	{
		m_selectedShape.ResetSelectShapePtr();
	}
	m_shapeViews.erase(m_shapeViews.begin() + index);
}

bool CCanvasView::HandleLButtonDown(const Vec2f point)
{
	bool isResize = false;
	if (m_selectedShape.HaveSelectedShape())
	{
		if (m_selectedShape.IsResize(point))
		{
			m_selectedShape.SetUpdateState(true);
			isResize = true;
			m_oldFrame = m_selectedShape.GetShape()->GetFrame();
			return true;
		}
	}

	if (!isResize)
	{
		ChangeSelectedShape(point);

		if (m_selectedShape.HaveSelectedShape())
		{
			if (m_selectedShape.IsMove(point))
			{
				m_selectedShape.SetUpdateState(true);
				m_oldFrame = m_selectedShape.GetShape()->GetFrame();
				return true;
			}
		}
	}

	if (m_selectedShape.HaveSelectedShape())
	{
		m_selectedShape.GetShape()->DoUnselected();
	}
	return false;
}

bool CCanvasView::HandleLButtonUp(const Vec2f point)
{
	if (m_selectedShape.HaveSelectedShape())
	{
		m_selectedShape.SetUpdateState(false);
	}

	if (m_selectedShape.DoneUpdate())
	{
		switch (m_selectedShape.GetUpdateType())
		{
		case CSelectedShape::UpdateType::Move:
		case CSelectedShape::UpdateType::MarkerLeftTop:
		case CSelectedShape::UpdateType::MarkerLeftBottom:
		case CSelectedShape::UpdateType::MarkerRightBottom:
		case CSelectedShape::UpdateType::MarkerRightTop:
		{
			return true;
		}
		break;
		case CSelectedShape::UpdateType::None:
			break;
		default:
			break;
		}
	}

	return false;
}

bool CCanvasView::HandleRButtonUp(const Vec2f point)
{
	return false;
}

bool CCanvasView::HandleMouseMove(const Vec2f point)
{
	if (m_selectedShape.HaveSelectedShape() && m_selectedShape.IsUpdate())
	{
		m_selectedShape.HandleMoveMouse(point);
		return true;
	}

	return false;
}

bool CCanvasView::DeleteSelectedShape()
{
	if (m_selectedShape.HaveSelectedShape())
	{
		m_deleteShape(GetShapeIndex(m_selectedShape.GetShape()));
		m_selectedShape.ResetSelectShapePtr();
		return true;
	}
	return false;
}

void CCanvasView::ResetSelectShapePtr()
{
	m_selectedShape.ResetSelectShapePtr();
}

void CCanvasView::SetBoundingRect(const D2D1_RECT_F & rect)
{
	m_selectedShape.SetBoundingRect(rect);
}

void CCanvasView::ChangeSelectedShape(const Vec2f & mousePos)
{
	auto selectShape = GetShape(mousePos, m_shapeViews);

	if (selectShape.get() != nullptr)
	{
		if (m_selectedShape.GetShape() != selectShape)
		{
			m_selectedShape.SetShape(selectShape);
		}
	}
	else
	{
		m_selectedShape.ResetSelectShapePtr();
	}
}

CursorType CCanvasView::ChangeCursor(const Vec2f & position)
{
	if (m_selectedShape.GetShape())
	{
		CSelectedShape::UpdateType updateType = m_selectedShape.GetUpdateType();
		bool needChangeToNW = (updateType == CSelectedShape::UpdateType::MarkerLeftTop)
			|| (updateType == CSelectedShape::UpdateType::MarkerRightBottom)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerLeftTop)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerRightBottom);
		bool needChangeToNE = (updateType == CSelectedShape::UpdateType::MarkerRightTop)
			|| (updateType == CSelectedShape::UpdateType::MarkerLeftBottom)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerRightTop)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerLeftBottom);

		if (needChangeToNW)
		{
			return CursorType::SIZENWSE;
		}
		else if (needChangeToNE)
		{
			return CursorType::SIZENESW;
		}
		else if (GetShape(position, m_shapeViews) != nullptr)
		{
			return CursorType::SIZEALL;
		}
	}
	else if (GetShape(position, m_shapeViews) != nullptr)
	{
		return CursorType::SIZEALL;
	}
	
	return CursorType::ARROW;
}

size_t CCanvasView::GetShapeIndex(const CShapeViewPtr & shapeView) const
{
	return std::find(m_shapeViews.begin(), m_shapeViews.end(), shapeView) - m_shapeViews.begin();
}

signal::Connection CCanvasView::DoOnDeleteShape(std::function<void(size_t)> const & action)
{
	return m_deleteShape.connect(action);
}

signal::Connection CCanvasView::DoOnChangeRectShape(std::function<void(const CFrame, size_t)> const & action)
{
	return m_createChangeRectCommand.connect(action);
}


CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector)
{
	CShapeViewPtr foundShape;
	for (auto iter = vector.rbegin(); iter != vector.rend(); ++iter)
	{
		if ((*iter)->IsPointIntersection(mousePosition))
		{
			foundShape = *iter;
			break;
		}
	}
	return foundShape;
}