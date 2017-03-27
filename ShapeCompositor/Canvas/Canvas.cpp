#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas()
	: m_size(640.f, 480.f)
{
}


void CCanvas::PushBackShape(CShapePtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvas::InsertShape(size_t insertIndex, CShapePtr & shape)
{
	CheckShapeIndex(insertIndex, true);

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);
}

size_t CCanvas::GetAmountShapes() const
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
	CheckShapeIndex(index);
	m_shapes.erase(m_shapes.begin() + index);
}

void CCanvas::DeleteShape(CShapePtr pShape)
{
	size_t index = GetIShapeIndex(pShape);
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
	CheckShapeIndex(index);

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

void CCanvas::AddAndExecuteCommand(const CanvasCommandPtr & command)
{
	m_history.AddAndExecuteCommand(command);
}

void CCanvas::UndoCommand()
{
	m_history.Undo();
}

void CCanvas::RedoCommand()
{
	m_history.Redo();
}

void CCanvas::ClearHistory()
{
	m_history.Clear();
}

void CCanvas::CheckShapeIndex(size_t index, bool isInsert) const
{
	const size_t checkValue = (isInsert) ? (index) : (index + 1);
	if (checkValue > m_shapes.size())
	{
		throw std::runtime_error("Index out range");
	}
}

size_t CCanvas::GetIShapeIndex(CShapePtr pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


