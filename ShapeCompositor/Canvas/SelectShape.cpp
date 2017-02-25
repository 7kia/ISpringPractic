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

void CSelectShape::SetStateUpdate(bool state)
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
			m_selectShape->SetPosition(curPos + shift);
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


void CSelectShape::SetViewPosition()
{
	SetMoveView();
	SetResizeView();
}

void CSelectShape::SetMoveView()
{
	SShapeData rectangleData = m_frameData;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape[0]->SetShapeData(rectangleData);

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
