#include "stdafx.h"
#include "GlobalFunctions.h"
#include "Canvas.h"

CCanvas::CCanvas(const SSize size)
	: m_size(size)
{
}


void CCanvas::PushBackShape(const CShapePtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::InsertShape(const size_t insertIndex, const CShapePtr & shape)
{
	CheckIndex(insertIndex, m_shapes.size());

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);
}

size_t CCanvas::GetShapeCount() const
{
	return m_shapes.size();
}

void CCanvas::SetSize(const SSize size)
{
	m_size = size;
}

SSize CCanvas::GetSize() const
{
	return m_size;
}

D2D1_RECT_F CCanvas::GetRect() const
{
	D2D1_RECT_F rect;
	rect.left = 0.f;
	rect.right = m_size.width;
	rect.top = 0.f;
	rect.bottom = m_size.height;
	return rect;
}

std::vector<CShapePtr>& CCanvas::GetShapes()
{
	return m_shapes;
}

bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapePtr> & shapes)
{
	for (const auto & shape : shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			auto pPicture = dynamic_cast<CPicture*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return true;
			}
		}
	}
	return false;
}

void CCanvas::SetShapes(const std::vector<CShapePtr> & shapes)
{
	m_shapes = shapes;
}

IShapeCollection & CCanvas::GetShapeCollection()
{
	return *this;
}

IShapeProvider & CCanvas::GetShapeProvider()
{
	return *this;
}

void CCanvas::DeleteShape(const size_t index)
{
	if (m_shapes.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	CheckIndex(index, m_shapes.size() - 1);
	m_shapes.erase(m_shapes.begin() + index);
}

void CCanvas::DeleteShape(const CShapePtr & pShape)
{
	size_t index = GetShapeIndex(pShape);
	if (index != size_t(-1))
	{
		DeleteShape(index);
	}
}

void CCanvas::Clear()
{
	m_shapes.clear();
}

CShapePtr CCanvas::GetShape(const size_t index)
{
	CheckIndex(index, m_shapes.size() - 1);

	return m_shapes[index];
}

CShapePtr CCanvas::GetShape(const ID2D1Bitmap * pTexture)
{
	for (const auto shape : m_shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			const auto pPicture = dynamic_cast<CPicture*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return shape;
			}
		}
	}
	return CShapePtr();
}

CShapePtr GetShape(const Vec2f mousePosition, const std::vector<CShapePtr> & vector)
{
	CShapePtr foundShape;
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

bool CCanvas::IsSelectShape(const size_t index, const CShapePtr & selectedShape) const
{
	return selectedShape == m_shapes[index];
}


size_t CCanvas::GetShapeIndex(const CShapePtr &  pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


