#include "stdafx.h"
#include "CanvasView.h"


bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapeViewPtr> & shapes)
{
	for (const auto & shape : shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			auto pPicture = dynamic_cast<CPictureView*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return true;
			}
		}
	}
	return false;
}


CCanvasView::CCanvasView()
{
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

void CCanvasView::AddShapeView(CShapeViewPtr & pView, size_t insertIndex)
{
	CheckIndex(insertIndex, m_shapeViews.size() - 1);

	m_shapeViews.insert(m_shapeViews.begin() + insertIndex, pView);
}

bool CCanvasView::HandleLButtonDown(const Vec2f point)
{
	ChangeCursor(point);

	bool isResize = false;
	if (m_selectedShape.HaveSelectedShape())
	{
		if (m_selectedShape.IsResize(point))
		{
			m_selectedShape.SetUpdateState(true);
			isResize = true;
			m_oldFrame = m_selectedShape.GetShape()->GetFrame();
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
			}
		}
	}

	return true;
}

bool CCanvasView::HandleLButtonUp(const Vec2f point)
{
	if (m_selectedShape.HaveSelectedShape())
	{
		m_selectedShape.SetUpdateState(false);
	}

	ChangeCursor(point);

	if (m_selectedShape.DoneUpdate())
	{
		CreateChangeRectCommand();
		m_selectedShape.ResetUpdateParameters();
	}

	return true;
}

bool CCanvasView::HandleRButtonUp(const Vec2f point)
{
	return false;
}

bool CCanvasView::HandleMouseMove(const Vec2f point)
{
	ChangeCursor(point);

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

void CCanvasView::ChangeCursor(const Vec2f & position)
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
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
			return;
		}
		else if (needChangeToNE)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
			return;
		}
		else if (GetShape(position, m_shapeViews) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
	}
	else
	{
		if (GetShape(position, m_shapeViews) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
		else
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
	}

}

void CCanvasView::CreateChangeRectCommand()
{
	switch (m_selectedShape.GetUpdateType())
	{
	case CSelectedShape::UpdateType::Move:
	case CSelectedShape::UpdateType::MarkerLeftTop:
	case CSelectedShape::UpdateType::MarkerLeftBottom:
	case CSelectedShape::UpdateType::MarkerRightBottom:
	case CSelectedShape::UpdateType::MarkerRightTop:
	{
		m_createChangeRectCommand(m_oldFrame, GetShapeIndex(m_selectedShape.GetShape()));
	}
	break;
	case CSelectedShape::UpdateType::None:
		break;
	default:
		break;
	}

}

size_t CCanvasView::GetShapeIndex(const CShapeViewPtr & shapeView)
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
