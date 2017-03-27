#include "stdafx.h"
#include "SelectedShape.h"

CSelectedShape::CSelectedShape(const CShapeFactory & shapeFactory)
	: IFrame()
{	
	SShapeData ellipseData;
	ellipseData.type = ShapeType::Ellipse;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = size_t(ShapeIndex::MarkerLeftBottom); index <= size_t(ShapeIndex::MarkerLeftTop); ++index)
	{
		m_resizeShapes[index] = shapeFactory.CreateShape(ellipseData);
	}

	SShapeData rectangleData;
	rectangleData.type = ShapeType::Rectangle;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_resizeShapes[size_t(ShapeIndex::Frame)] = shapeFactory.CreateShape(rectangleData);
}

void CSelectedShape::SetShape(CShapePtr shape)
{
	m_selectedShape = shape;
	m_frameData = shape->GetShapeData();
	m_oldData = m_frameData;

	SetViewPosition();
}

CShapePtr CSelectedShape::GetShape() const
{
	return m_selectedShape;
}

void CSelectedShape::ResetSelectShapePtr()
{
	m_selectedShape = nullptr;
	m_isUpdate = false;

	m_oldData = SFrameData();
}

void CSelectedShape::ResetUpdateParameters()
{
	m_startMove.reset();
	m_start = Vec2f();
	m_current = Vec2f();
	m_isUpdate = false;
	m_updateType = UpdateType::None;

	m_oldData = m_frameData;

}

void CSelectedShape::SetUpdateState(bool state)
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
	size_t index = size_t(UpdateType::MarkerLeftBottom);
	for (const auto & resizeShape : m_resizeShapes)
	{
		if (resizeShape->IsPointIntersection(point))
		{
			SetUpdateType(UpdateType(index));
			return true;
		}
		++index;
	}


	return false;
}

bool CSelectedShape::InLeftTopMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(ShapeIndex::MarkerLeftTop)]->IsPointIntersection(point);
}

bool CSelectedShape::InLeftBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(ShapeIndex::MarkerLeftBottom)]->IsPointIntersection(point);
}

bool CSelectedShape::InRightTopMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(ShapeIndex::MarkerRightTop)]->IsPointIntersection(point);
}

bool CSelectedShape::InRightBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(ShapeIndex::MarkerRightBottom)]->IsPointIntersection(point);
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

			SetFrameData(GetCurrentFrameData());
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
	}

	m_frameData.position = position;

	SetViewPosition();
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
	m_frameData.size = size;

	for (auto & shape : m_resizeShapes)
	{
		shape->SetSize(size);
	}
}

SSize CSelectedShape::GetSize() const
{
	return m_selectedShape->GetSize();
}


SRectF CSelectedShape::GetOwnRect() const
{
	return GetFrameRect(m_selectedShape->GetSize(), m_selectedShape->GetPosition());
}

SFrameData CSelectedShape::GetFrameData() const
{
	SFrameData info;
	info.position = m_frameData.position;
	info.size = m_frameData.size;

	return info;
}

void CSelectedShape::SetFrameData(SFrameData const & data)
{
	if (HaveSelectedShape())
	{
		m_selectedShape->SetFrameData(data);
	}

	m_frameData.position = data.position;
	m_frameData.size = data.size;
	SetViewPosition();
}


Vec2f CSelectedShape::GetFinalShift() const
{
	if (m_startMove)
	{
		return m_current - *m_startMove;
	}
	return m_current;
}

void CSelectedShape::MoveFrame(const Vec2f shift)
{
	m_frameData.position = m_frameData.position + shift;
	SetViewPosition();
}


SFrameData CSelectedShape::GetNewFrameData() const
{
	return GetFrameData(GetFinalShift());
}

SFrameData CSelectedShape::GetOldFrameData()
{
	return m_oldData;
}

SFrameData CSelectedShape::GetCurrentFrameData()
{
	return GetFrameData(m_current - m_start);
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

void CSelectedShape::ReturnToOldState()
{
	SetFrameData(GetOldFrameData());
}

void CSelectedShape::SetViewPosition()
{
	SetMoveView();
	SetResizeView();
}

void CSelectedShape::SetMoveView()
{
	m_resizeShapes[size_t(ShapeIndex::Frame)]->SetFrameData(GetFrameData());
}

void CSelectedShape::SetResizeView()
{
	auto vertices = m_frameData.GetFrameVertices();// m_selectedShape->
	size_t indexEllipse = 0;
	for (const auto & vertex : vertices)
	{
		SShapeData ellipseData;
		ellipseData.position = vertex;
		ellipseData.size = SELECTED_ELLIPSE_SIZE;
		ellipseData.outlineColor = BLACK_COLOR;
		ellipseData.fillColor = BLACK_COLOR;

		m_resizeShapes[indexEllipse++]->SetShapeData(ellipseData);
	}
}

bool CSelectedShape::CheckSize(const SSize size) const
{
	return (size.width >= MIN_SHAPE_SIZE.width) && (size.height >= MIN_SHAPE_SIZE.height);
}

SFrameData CSelectedShape::GetFrameData(const Vec2f shift) const
{
	SFrameData info;
	SSize directionResize = GetDirectionResize();

	if ( (m_updateType != UpdateType::Move) && (m_updateType != UpdateType::None))
	{
		info.size = GetCorrectSize(m_frameData.size + (SSize(shift.x * directionResize.width, shift.y * directionResize.height)));
		SSize & newSize = info.size;
		Vec2f differentSizes = Vec2f(newSize.width - m_frameData.size.width, newSize.height - m_frameData.size.height);
		info.position = GetCorrectPosition(newSize, Vec2f(differentSizes.x / 2.f * directionResize.width
			, differentSizes.y / 2.f * directionResize.height), m_frameData.position);
	}
	else if(m_updateType == UpdateType::Move)
	{
		info.position = m_frameData.position + shift;
	}

	return info;
}

SSize CSelectedShape::GetCorrectSize(const SSize size) const
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

Vec2f CSelectedShape::GetCorrectPositionShift(
	const Vec2f shift
	, bool conditionForX
	, bool conditionForY
) const
{
	Vec2f correctShift = shift;
	if (conditionForX)
	{
		correctShift.x = 0.f;
	}
	if (conditionForY)
	{
		correctShift.y = 0.f;
	}
	return correctShift;
}

CSelectedShape::ArrayShapes CSelectedShape::GetShapes() const
{
	return m_resizeShapes;
}

