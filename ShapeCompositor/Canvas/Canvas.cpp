#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas()
	: IDrawable()
	, CFrame(Vec2f(), SSize(640.f, 480.f))
{
}

void CCanvas::Accept(IObjectVisitor & renderer) const
{
	renderer.Visit(*this);
}


void CCanvas::PushBackShape(CShapePtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::InsertShape(size_t insertIndex, CShapePtr & shape)
{
	CheckIndex(insertIndex);

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);
}

size_t CCanvas::GetAmountShapes() const
{
	return m_shapes.size();
}

std::vector<CShapePtr> CCanvas::GetShapes() const
{
	return m_shapes;
}

void CCanvas::SetShapes(const std::vector<CShapePtr>& shapes)
{
	m_shapes = shapes;
}

void CCanvas::DeleteShape(size_t index)
{
	CheckIndex(index);
	m_shapes.erase(m_shapes.begin() + index);
}

void CCanvas::DeleteShape(CShapePtr pShape)
{
	size_t index = GetIndexShape(pShape);
	if (index != size_t(-1))
	{
		DeleteShape(index);
	}
}

void CCanvas::DeleteLastShape()
{
	DeleteShape(m_shapes.size() - 1);
}

void CCanvas::Clear()
{
	m_shapes.clear();
}

CShapePtr CCanvas::GetShape(size_t index)
{
	CheckIndex(index);

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

size_t CCanvas::GetShapeIndex(const CShapePtr pShape) const
{
	const auto iter = std::find_if(
		m_shapes.begin()
		, m_shapes.end()
		, [&](CShapePtr pElement)
		{
			if (pShape == pElement)
			{
				return true;
			}
			return false;
		}
	);

	return iter - m_shapes.begin();
}

bool CCanvas::IsSelectShape(size_t index, const CShapePtr selectedShape) const
{
	return selectedShape == m_shapes[index];
}

void CCanvas::CheckIndex(size_t index) const
{
	size_t maxValue = (m_shapes.size() > 0) ? m_shapes.size() - 1 : m_shapes.size();
	if (!IsBetween(index, size_t(0), maxValue))
	{
		throw std::runtime_error("Index out range");
	}
}

size_t CCanvas::GetIndexShape(CShapePtr pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


