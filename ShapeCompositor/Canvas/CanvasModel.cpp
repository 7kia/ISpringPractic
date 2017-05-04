#include "stdafx.h"
#include "GlobalFunctions.h"
#include "CanvasModel.h"

CCanvasModel::CCanvasModel(const SSize size)
	: m_size(size)
{
}


void CCanvasModel::PushBackShape(const CShapeModelPtr & shape)
{
	m_shapes.push_back(shape);
}

void CCanvasModel::InsertShape(const size_t insertIndex, const CShapeModelPtr & shape)
{
	CheckIndex(insertIndex, m_shapes.size());

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);
}

size_t CCanvasModel::GetShapeCount() const
{
	return m_shapes.size();
}

void CCanvasModel::SetSize(const SSize size)
{
	m_size = size;
}

SSize CCanvasModel::GetSize() const
{
	return m_size;
}

D2D1_RECT_F CCanvasModel::GetRect() const
{
	D2D1_RECT_F rect;
	rect.left = 0.f;
	rect.right = m_size.width;
	rect.top = 0.f;
	rect.bottom = m_size.height;
	return rect;
}

std::vector<CShapeModelPtr>& CCanvasModel::GetShapes()
{
	return m_shapes;
}

void CCanvasModel::SetShapes(const std::vector<CShapeModelPtr> & shapes)
{
	m_shapes = shapes;
}

IShapeCollection & CCanvasModel::GetShapeCollection()
{
	return *this;
}

IShapeProvider & CCanvasModel::GetShapeProvider()
{
	return *this;
}

void CCanvasModel::DeleteShape(const size_t index)
{
	if (m_shapes.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	CheckIndex(index, m_shapes.size() - 1);
	m_shapes.erase(m_shapes.begin() + index);
}

void CCanvasModel::DeleteShape(const CShapeModelPtr & pShape)
{
	size_t index = GetShapeIndex(pShape);
	if (index != size_t(-1))
	{
		DeleteShape(index);
	}
}

void CCanvasModel::Clear()
{
	m_shapes.clear();
}

CShapeModelPtr CCanvasModel::GetShape(const size_t index)
{
	CheckIndex(index, m_shapes.size() - 1);

	return m_shapes[index];
}

CShapeModelPtr CCanvasModel::GetShape(const ID2D1Bitmap * pTexture)
{
	for (const auto shape : m_shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			const auto pPicture = dynamic_cast<CPictureView*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return shape;
			}
		}
	}
	return CShapeModelPtr();
}

CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector)
{
	CShapeViewPtr foundShape;
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

bool CCanvasModel::IsSelectShape(const size_t index, const CShapeModelPtr & selectedShape) const
{
	return selectedShape == m_shapes[index];
}


size_t CCanvasModel::GetShapeIndex(const CShapeModelPtr &  pShape) const
{
	return  std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


