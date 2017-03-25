#include "stdafx.h"
#include "SelectedShape.h"

CSelectedShape::CSelectedShape(const CShapeFactory & shapeFactory)
	: IDrawable()
{
	SShapeData rectangleData;
	rectangleData.type = ShapeType::Rectangle;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape.push_back(shapeFactory.CreateShape(rectangleData));
	
	SShapeData ellipseData;
	ellipseData.type = ShapeType::Ellipse;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		m_resizeShapes[index] = shapeFactory.CreateShape(ellipseData);
	}
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
	m_startMove = Vec2f();
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
	return m_resizeShapes[size_t(Marker::MarkerLeftTop)]->IsPointIntersection(point);
}

bool CSelectedShape::InLeftBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerLeftBottom)]->IsPointIntersection(point);
}

bool CSelectedShape::InRightTopMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerRightTop)]->IsPointIntersection(point);
}

bool CSelectedShape::InRightBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerRightBottom)]->IsPointIntersection(point);
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
			if (m_startMove == Vec2f())
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

void CSelectedShape::Accept(IObjectVisitor & renderer) const
{
	if (m_selectedShape != nullptr)
	{
		for (auto & shape : m_moveShape)
		{
			shape->Accept(renderer);
		}
		for (auto & shape : m_resizeShapes)
		{
			shape->Accept(renderer);
		}
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

	for (auto & shape : m_moveShape)
	{
		shape->SetSize(size);
	}
	for (auto & shape : m_resizeShapes)
	{
		shape->SetSize(size);
	}
}

SSize CSelectedShape::GetSize() const
{
	return m_selectedShape->GetSize();
}

void CSelectedShape::UpdateScale(const Vec2f shift)
{
	SetSize(GetSize() + SSize(shift.x, shift.y));
	Move(Vec2f(shift.x / 2.f, shift.y / 2.f));
}

SRectF CSelectedShape::GetOwnRect() const
{
	return m_selectedShape->GetOwnRect();
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
	return m_current - m_startMove;
}

void CSelectedShape::MoveFrame(const Vec2f shift)
{
	m_frameData.position = m_frameData.position + shift;
	SetViewPosition();
}


SFrameData CSelectedShape::GetNewFrameData() const
{
	SFrameData info;
	const Vec2f shift = GetFinalShift();
	SSize directionResize = GetDirectionResize();
	const SSize newSize = m_frameData.size + (SSize(shift.x * directionResize.width, shift.y * directionResize.height));

	const Vec2f directionShift = GetDirectionShift(Vec2f(shift.x / 2.f, shift.y / 2.f));
	info.position = GetCorrectPosition(newSize, Vec2f(shift.x / 2.f, shift.y / 2.f), m_frameData.position);

	info.size = GetCorrectSize(newSize);

	return info;
}

SFrameData CSelectedShape::GetOldFrameData()
{
	return m_oldData;
}

SFrameData CSelectedShape::GetCurrentFrameData()
{
	SFrameData info;
	const Vec2f shift = m_current - m_start;
	SSize directionResize = GetDirectionResize();

	const SSize newSize = m_frameData.size + (SSize(shift.x * directionResize.width, shift.y * directionResize.height));

	const Vec2f directionShift = GetDirectionShift(Vec2f(shift.x / 2.f, shift.y / 2.f));
	info.position = GetCorrectPosition(newSize, Vec2f(shift.x / 2.f, shift.y / 2.f), m_frameData.position);
	info.size = GetCorrectSize(newSize);

	return info;
}

SSize CSelectedShape::GetDirectionResize() const
{
	SSize result;
	switch (m_updateType)
	{
		case UpdateType::MarkerLeftTop:
		{
			return SSize(-1.f, -1.f);
		}
		break;
		case UpdateType::MarkerLeftBottom:
		{
			return SSize(-1.f, 1.f);
		}
		break;
		case UpdateType::MarkerRightBottom:
		{
			return SSize(1.f, 1.f);
		}
		break;
		case UpdateType::MarkerRightTop:
		{
			return SSize(1.f, -1.f);
		}
		break;
		default:
			break;
	}
	return SSize();
}

Vec2f CSelectedShape::GetDirectionShift(const Vec2f shift) const
{
	switch (m_updateType)
	{
		case UpdateType::MarkerLeftTop:
		{		
			return GetCorrectShift(shift, shift.x > 0, shift.y > 0);
		}
		break;
		case UpdateType::MarkerLeftBottom:
		{
			return GetCorrectShift(shift, shift.x > 0, shift.y < 0);
		}
		break;
		case UpdateType::MarkerRightBottom:
		{
			return GetCorrectShift(shift, shift.x < 0, shift.y < 0);
		}
		break;
		case UpdateType::MarkerRightTop:
		{
			return GetCorrectShift(shift, shift.x < 0, shift.y > 0);
		}
		break;
		default:
			break;
	}
	return Vec2f();
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
	m_moveShape[0]->SetFrameData(GetFrameData());
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
	Vec2f result = startPosition;
	if (CheckSize(newSize))
	{
		result = result + shift;
	}

	return result;
}


Vec2f CSelectedShape::GetCorrectShift(
	const Vec2f & shift
	, bool conditionForX
	, bool conditionForY
) const
{
	Vec2f result = shift;
	if (conditionForX)
	{
		result.x = 0.f;
	}
	if (conditionForY)
	{
		result.y = 0.f;
	}
	return result;
}
