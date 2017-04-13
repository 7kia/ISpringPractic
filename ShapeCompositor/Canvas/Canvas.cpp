#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(const SSize & size, const CShapePtr & view)
	: m_size(size)
	, m_view(view)
{
}


void CCanvas::PushBackShape(const CShapePtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::InsertShape(size_t insertIndex, const CShapePtr & shape)
{
	CheckIndex(insertIndex, m_shapes.size());

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);
}

size_t CCanvas::GetAmountShapes() const
{
	return m_shapes.size();
}

void CCanvas::SetSize(const SSize & size)
{
	m_size = size;
}

SSize CCanvas::GetSize() const
{
	return m_size;
}

CShapePtr CCanvas::GetView() const
{
	return m_view;
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

void CCanvas::DeleteShape(size_t index)
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

CShapePtr CCanvas::GetShape(size_t index)
{
	CheckIndex(index, m_shapes.size() - 1);

	return m_shapes[index];
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

bool CCanvas::IsSelectShape(size_t index, const CShapePtr & selectedShape) const
{
	return selectedShape == m_shapes[index];
}


size_t CCanvas::GetShapeIndex(const CShapePtr &  pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


