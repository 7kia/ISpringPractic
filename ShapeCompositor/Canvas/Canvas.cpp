#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(const SSize & size)
	: m_size(size)
{
}


void CCanvas::PushBackShape(const CShapePtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::InsertShape(size_t insertIndex, const CShapePtr & shape)
{
	CheckShapeIndex(insertIndex, m_shapes.size());

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

std::vector<CShapePtr> CCanvas::GetShapes() const
{
	return m_shapes;
}

void CCanvas::SetShapes(const std::vector<CShapePtr> & shapes)
{
	m_shapes = shapes;
}

void CCanvas::DeleteShape(size_t index)
{
	if (m_shapes.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	CheckShapeIndex(index, m_shapes.size() - 1);
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

void CCanvas::DeleteLastShape()
{
	if (m_shapes.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	DeleteShape(m_shapes.size() - 1);
}

void CCanvas::Clear()
{
	m_shapes.clear();
}

CShapePtr CCanvas::GetShape(size_t index)
{
	CheckShapeIndex(index, m_shapes.size() - 1);

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

void CCanvas::CheckShapeIndex(size_t index, size_t max) const
{
	if (index > max)
	{
		throw std::runtime_error("Index out range");
	}
}

size_t CCanvas::GetShapeIndex(const CShapePtr &  pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


