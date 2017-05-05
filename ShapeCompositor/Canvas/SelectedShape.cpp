#include "stdafx.h"
#include "GlobalFunctions.h"
#include "SelectedShape.h"

CSelectedShape::CSelectedShape()
{	
	for (size_t index = size_t(ShapeIndex::MarkerLeftBottom); index <= size_t(ShapeIndex::MarkerLeftTop); ++index)
	{
		m_dragPoints[index] = std::make_shared<CEllipseView>(
			Vec2f(),
			SELECTED_ELLIPSE_SIZE,
			BLACK_COLOR,
			BLACK_COLOR
		);
	}

	m_frame = std::make_shared<CRectangleView>(
		Vec2f(),
		SSize(),
		NOT_COLOR,
		BLACK_COLOR,
		2.f
	);
}

void CSelectedShape::SetShape(const CShapeViewPtr & shape)
{
	m_selectedShape = shape;
	m_setFrameConnection = m_selectedShape->DoOnRectChanged(boost::bind(&IFrame::SetFrame, this, _1));
	SetDragPointPositions();
}

CShapeViewPtr CSelectedShape::GetShape() const
{
	return m_selectedShape;
}

void CSelectedShape::ResetSelectShapePtr()
{
	m_selectedShape = nullptr;
	m_isUpdate = false;

}

void CSelectedShape::ResetUpdateParameters()
{
	m_startMove.reset();
	m_start = Vec2f();
	m_current = Vec2f();
	m_isUpdate = false;
	m_updateType = UpdateType::None;

}

void CSelectedShape::SetUpdateState(const bool state)
{
	m_isUpdate = state;
}

bool CSelectedShape::IsUpdate() const
{
	return m_isUpdate;
}

bool CSelectedShape::HaveSelectedShape() const
{
	return m_selectedShape.get() != nullptr;
}

void CSelectedShape::SetUpdateType(UpdateType type)
{
	m_updateType = type;
}

CSelectedShape::UpdateType CSelectedShape::GetUpdateType() const
{
	return m_updateType;
}

bool CSelectedShape::IsResize(const Vec2f point)
{
	for(size_t index = size_t(ShapeIndex::MarkerLeftBottom); index <= size_t(ShapeIndex::MarkerLeftTop); ++index)
	{
		if (m_dragPoints[index]->IsPointIntersection(point))
		{
			SetUpdateType(UpdateType(index));
			return true;
		}
	}


	return false;
}

bool CSelectedShape::InMarker(const Vec2f point, const ShapeIndex markerIndex)
{
	return m_dragPoints[size_t(markerIndex)]->IsPointIntersection(point);
}

bool CSelectedShape::DoneUpdate() const
{
	return HaveSelectedShape()
		&& !IsUpdate()
		&& (GetFinalShift() != Vec2f());
}

bool CSelectedShape::IsMove(const Vec2f point)
{
	if (m_selectedShape->IsPointIntersection(point))
	{
		SetUpdateType(UpdateType::Move);
		return true;
	}
	return false;
}

void CSelectedShape::HandleMoveMouse(const Vec2f point)
{
	switch (m_updateType)
	{
	case UpdateType::None:
		{

		}
		break;
	case UpdateType::MarkerLeftTop:
	case UpdateType::MarkerLeftBottom:
	case UpdateType::MarkerRightBottom:
	case UpdateType::MarkerRightTop:
	case UpdateType::Move:
		{
			if (!m_startMove)
			{
				m_startMove = point;
				m_start = point;
			}

			m_current = point;

			SetFrame(GetNewFrame(m_current - m_start, m_selectedShape->GetFrame()));
			m_start = m_current;
			
		}
		break;
	default:
		break;
	}
}


void CSelectedShape::SetPosition(Vec2f position)
{
	if (HaveSelectedShape())
	{
		m_selectedShape->SetPosition(position);

		SetDragPointPositions();
		m_frame->SetPosition(position);
	}
}

Vec2f CSelectedShape::GetPosition() const
{
	if (!HaveSelectedShape())
	{
		throw std::runtime_error("Not selected shape");
	}

	return m_selectedShape->GetPosition();
}

void CSelectedShape::Move(const Vec2f shift)
{
	SetPosition(GetPosition() + shift);
}

void CSelectedShape::SetSize(SSize size)
{
	if (HaveSelectedShape())
	{
		m_selectedShape->SetSize(size);
	}

	for (auto & shape : m_dragPoints)
	{
		shape->SetSize(size);
	}
}

SSize CSelectedShape::GetSize() const
{
	return m_selectedShape->GetSize();
}

CFrame CSelectedShape::GetFrame() const
{
	if (HaveSelectedShape())
	{
		return m_selectedShape->GetFrame();
	}
	return CFrame();
}

void CSelectedShape::SetFrame(CFrame const & data)
{
	if (HaveSelectedShape())
	{
		m_selectedShape->SetFrame(data);
		SetDragPointPositions();
		m_frame->SetFrame(data);
	}
}


Vec2f CSelectedShape::GetFinalShift() const
{
	if (m_startMove)
	{
		return m_current - *m_startMove;
	}
	return Vec2f();
}


SSize CSelectedShape::GetDirectionResize() const
{
	switch (m_updateType)
	{
		case UpdateType::MarkerLeftTop:
		{
			return SSize(-1.f, -1.f);
		}
		case UpdateType::MarkerLeftBottom:
		{
			return SSize(-1.f, 1.f);
		}
		case UpdateType::MarkerRightBottom:
		{
			return SSize(1.f, 1.f);
		}
		case UpdateType::MarkerRightTop:
		{
			return SSize(1.f, -1.f);
		}
	}
	return SSize();
}



bool CSelectedShape::CheckBoundingRect(const D2D1_RECT_F & rect) const
{
	bool leftCorrect = IsBetween(rect.left, m_boundingRect.left, m_boundingRect.right);
	bool rightCorrect = IsBetween(rect.right, m_boundingRect.left, m_boundingRect.right);
	bool topCorrect = IsBetween(rect.top, m_boundingRect.top, m_boundingRect.bottom);
	bool bottomCorrect = IsBetween(rect.bottom, m_boundingRect.top, m_boundingRect.bottom);

	return leftCorrect && rightCorrect && topCorrect && bottomCorrect;
}

void CSelectedShape::SetDragPointPositions()
{
	const auto vertices = m_selectedShape->GetFrameVertices();
	for (size_t index = size_t(ShapeIndex::MarkerLeftBottom); index <= size_t(ShapeIndex::MarkerLeftTop); ++index)
	{
		m_dragPoints[index]->SetPosition(vertices[index]);
	}
}

bool CSelectedShape::CheckSize(const SSize size) const
{
	return (size.width >= MIN_SHAPE_SIZE.width) && (size.height >= MIN_SHAPE_SIZE.height);
}

CFrame CSelectedShape::GetNewFrame(const Vec2f shift, const CFrame & oldFrame) const
{
	CFrame info;


	switch (m_updateType)
	{
	case UpdateType::Move:
		{
			info.SetPosition(oldFrame.GetPosition() + shift);
			info.SetSize(oldFrame.GetSize());
		}
		break;
	case UpdateType::MarkerLeftTop:
	case UpdateType::MarkerLeftBottom:
	case UpdateType::MarkerRightBottom:
	case UpdateType::MarkerRightTop:
		{
			SSize directionResize = GetDirectionResize();

			const SSize frameSize = oldFrame.GetSize();
			info.SetSize(GetCorrectSize(frameSize + SSize(shift.x * directionResize.width, shift.y * directionResize.height)));

			const SSize newSize = info.GetSize();
			const Vec2f differentSizes = Vec2f(newSize.width - frameSize.width, newSize.height - frameSize.height);
			const Vec2f positionShift = Vec2f(differentSizes.x  * directionResize.width / 2.f
												, differentSizes.y * directionResize.height / 2.f);
			const Vec2f framePosition = oldFrame.GetPosition();
			info.SetPosition(GetCorrectPosition(newSize, positionShift, framePosition));
		}
		break;
	default:
		break;
	}
	if (CheckBoundingRect(GetFrameRect(info)))
	{
		return info;
	}

	return oldFrame;
}

SSize CSelectedShape::GetCorrectSize(const SSize size)
{
	SSize result = size;
	if (result.width < MIN_SHAPE_SIZE.width)
	{
		result.width = MIN_SHAPE_SIZE.width;
	}
	if (result.height < MIN_SHAPE_SIZE.height)
	{
		result.height = MIN_SHAPE_SIZE.height;
	}
	return result;
}

Vec2f CSelectedShape::GetCorrectPosition(
	const SSize newSize
	, const Vec2f shift
	, const Vec2f startPosition
) const
{
	Vec2f correctShift = shift;
	bool widthIsCorrect = newSize.width >= MIN_SHAPE_SIZE.width;
	bool heightIsCorrect = newSize.height >= MIN_SHAPE_SIZE.height;
	if (!widthIsCorrect)
	{
		correctShift.x = 0.f;
	}
	if (!heightIsCorrect)
	{
		correctShift.y = 0.f;
	}

	if (widthIsCorrect || heightIsCorrect)
	{
		return startPosition + correctShift;
	}

	return startPosition;
}


CSelectedShape::DragPointsArray CSelectedShape::GetDragPoints() const
{
	return m_dragPoints;
}

CShapeViewPtr CSelectedShape::GetFrameShape() const
{
	return m_frame;
}

void CSelectedShape::SetBoundingRect(const D2D1_RECT_F & rect)
{
	m_boundingRect = rect;
}

