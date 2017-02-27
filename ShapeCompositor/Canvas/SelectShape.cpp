#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CD2DObjectRenderer & shapeRenderer, const CShapeFactory & shapeFactory)
	: IDrawable()
{
	SShapeData rectangleData;
	rectangleData.type = ShapeType::Rectangle;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape.push_back(shapeFactory.CreateShape(rectangleData, shapeRenderer));
	
	SShapeData ellipseData;
	ellipseData.type = ShapeType::Ellipse;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		m_resizeShapes[index] = shapeFactory.CreateShape(ellipseData, shapeRenderer);
	}
}

void CSelectShape::SetShape(CShapePtr shape)
{
	m_selectShape = shape;
	m_frameData = shape->GetShapeData();
	m_oldData = m_frameData;

	SetViewPosition();
}

CShapePtr CSelectShape::GetShape() const
{
	return m_selectShape;
}

void CSelectShape::ResetSelectShapePtr()
{
	m_selectShape = nullptr;
	m_isUpdate = false;

	m_oldData = SFrameData();
}

void CSelectShape::ResetUpdateParameters()
{
	m_startMove = Vec2f();
	m_start = Vec2f();
	m_current = Vec2f();
	m_isUpdate = false;
	m_updateType = UpdateType::None;

	m_oldData = m_frameData;

}

void CSelectShape::SetUpdateState(bool state)
{
	m_isUpdate = state;
}

bool CSelectShape::IsUpdate() const
{
	return m_isUpdate;
}

bool CSelectShape::HaveSelectedShape() const
{
	return m_selectShape.get() != nullptr;
}

void CSelectShape::SetUpdateType(UpdateType type)
{
	m_updateType = type;
}

CSelectShape::UpdateType CSelectShape::GetUpdateType() const
{
	return m_updateType;
}

bool CSelectShape::IsResize(const Vec2f point)
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

bool CSelectShape::InLeftTopMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerLeftTop)]->IsPointIntersection(point);
}

bool CSelectShape::InLeftBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerLeftBottom)]->IsPointIntersection(point);
}

bool CSelectShape::InRightTopMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerRightTop)]->IsPointIntersection(point);
}

bool CSelectShape::InRightBottomMarker(const Vec2f point)
{
	return m_resizeShapes[size_t(Marker::MarkerRightBottom)]->IsPointIntersection(point);
}

bool CSelectShape::IsMove(const Vec2f point)
{
	if (m_selectShape->IsPointIntersection(point))
	{
		SetUpdateType(UpdateType::Move);
		return true;
	}
	return false;
}

void CSelectShape::HandleMoveMouse(const Vec2f point)
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

void CSelectShape::Accept(IShapeVisitor & renderer) const
{
	if (m_selectShape != nullptr)
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


void CSelectShape::SetPosition(Vec2f position)
{
	if (HaveSelectedShape())
	{
		m_selectShape->SetPosition(position);
	}

	m_frameData.position = position;

	SetViewPosition();
}

Vec2f CSelectShape::GetPosition() const
{
	if (!HaveSelectedShape())
	{
		throw std::runtime_error("Not selected shape");
	}

	return m_selectShape->GetPosition();
}

void CSelectShape::Move(const Vec2f shift)
{
	SetPosition(GetPosition() + shift);
}

void CSelectShape::SetSize(SSize size)
{
	if (HaveSelectedShape())
	{
		m_selectShape->SetSize(size);
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

SSize CSelectShape::GetSize() const
{
	return m_selectShape->GetSize();
}

void CSelectShape::UpdateScale(const Vec2f shift)
{
	SetSize(GetSize() + SSize(shift.x, shift.y));
	Move(Vec2f(shift.x / 2.f, shift.y / 2.f));
}

RECT CSelectShape::GetOwnRect() const
{
	return m_selectShape->GetOwnRect();
}

SFrameData CSelectShape::GetFrameData() const
{
	SFrameData info;
	info.position = m_frameData.position;
	info.size = m_frameData.size;

	return info;
}

void CSelectShape::SetFrameData(SFrameData const & data)
{
	if (HaveSelectedShape())
	{
		m_selectShape->SetFrameData(data);
	}

	m_frameData.position = data.position;
	m_frameData.size = data.size;
	SetViewPosition();
}


Vec2f CSelectShape::GetShift() const
{
	return m_current - m_startMove;
}

void CSelectShape::MoveFrame(const Vec2f shift)
{
	m_frameData.position = m_frameData.position + shift;
	SetViewPosition();
}


SFrameData CSelectShape::GetNewFrameData() const
{
	SFrameData info;
	const Vec2f shift = GetShift();
	SSize resize = GetChangeResize();
	
	info.position = m_frameData.position + (Vec2f(shift.x / 2.f, shift.y / 2.f));
	info.size = m_frameData.size + (SSize(shift.x * resize.width, shift.y * resize.height) );

	return info;
}

SFrameData CSelectShape::GetOldFrameData()
{
	return m_oldData;
}

SFrameData CSelectShape::GetCurrentFrameData()
{
	SFrameData info;
	const Vec2f shift = m_current - m_start;
	SSize resize = GetChangeResize();

	const float shiftFactor = (m_updateType == UpdateType::Move) ? 1.f : 1.f / 2.f;
	info.position = m_frameData.position + (Vec2f(shift.x * shiftFactor, shift.y * shiftFactor));
	info.size = m_frameData.size + (SSize(shift.x * resize.width, shift.y * resize.height));

	return info;
}

SSize CSelectShape::GetChangeResize() const
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

void CSelectShape::ReturnToOldState()
{
	SetFrameData(GetOldFrameData());
}

void CSelectShape::SetViewPosition()
{
	SetMoveView();
	SetResizeView();
}

void CSelectShape::SetMoveView()
{
	m_moveShape[0]->SetFrameData(GetFrameData());
}

void CSelectShape::SetResizeView()
{
	auto vertices = m_frameData.GetFrameVertices();// m_selectShape->
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
