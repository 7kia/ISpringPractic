#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CD2DObjectRenderer & shapeRenderer, const CShapeFactory & shapeFactory)
	: IDrawable()
{
	SShapeData rectangleData;
	rectangleData.type = TypeShape::Rectangle;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape.push_back(shapeFactory.CreateShape(rectangleData, shapeRenderer));
	
	SShapeData ellipseData;
	ellipseData.type = TypeShape::Ellipse;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		m_resizeShapes.push_back(shapeFactory.CreateShape(ellipseData, shapeRenderer));
	}
}

void CSelectShape::SetShape(CShapePtr shape)
{
	m_selectShape = shape;
	m_frameData = shape->GetShapeData();

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
}

void CSelectShape::ResetUpdateParameters()
{
	m_startMove = Vec2f();
	m_start = Vec2f();
	m_current = Vec2f();
	m_end = Vec2f();
	m_isUpdate = false;
	m_updateType = UpdateType::None;
}

void CSelectShape::SetStateUpdate(bool state)
{
	m_isUpdate = state;

	if (!m_isUpdate)
	{
		m_end = Vec2f();
	}
}

bool CSelectShape::GetUpdateState() const
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
	for (const auto & resizeShape : m_resizeShapes)
	{
		if (resizeShape->IsPointIntersection(point))
		{
			SetUpdateType(UpdateType::Resize);
			return true;
		}
	}
	return false;
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
	case UpdateType::Resize:
		{

		}
		break;
	case UpdateType::Move:
		{
			if (m_startMove == Vec2f())
			{
				m_startMove = point;
				m_start = point;
			}
			m_current = point;

			Vec2f shift = m_current - m_start;
			Vec2f curPos = m_selectShape->GetPosition();
			//m_current = 
			m_end = curPos + shift;
			//SetPosition(curPos + shift);
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

bool CSelectShape::DefineUpdateType(const Vec2f point)
{
	if (HaveSelectedShape())
	{
		for (const auto & resizeShape : m_resizeShapes)
		{
			if (resizeShape->IsPointIntersection(point))
			{
				SetUpdateType(UpdateType::Resize);
				return true;
			}
		}
		if (m_selectShape->IsPointIntersection(point))
		{
			SetUpdateType(UpdateType::Move);
			return true;
		}
	}
	return false;
}

void CSelectShape::SetPosition(Vec2f position)
{
	m_selectShape->SetPosition(position);
	m_frameData.position = position;

	SetViewPosition();
}

Vec2f CSelectShape::GetPosition() const
{
	return m_selectShape->GetPosition();
}

void CSelectShape::Move(const Vec2f shift)
{
	SetPosition(GetPosition() + shift);
}

void CSelectShape::SetSize(SSize size)
{
	m_selectShape->SetSize(size);
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
	m_frameData.position = data.position;
	m_frameData.size = data.size;
}


Vec2f CSelectShape::GetShift() const
{
	const Vec2f result = m_current - m_startMove;
	return  m_current - m_startMove;
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
	auto vertices = m_selectShape->GetFrameVertices();
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
