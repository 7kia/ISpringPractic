#include "stdafx.h"
#include "GlobalFunctions.h"
#include "CanvasModel.h"
#include "Shapes/Presenter/ShapePresenter.h"

CCanvasModel::CCanvasModel(const SSize size)
	: m_size(size)
{
}


void CCanvasModel::PushBackShape(CShapeModelPtr & shape)
{
	m_shapes.push_back(shape);

	auto view = m_shapeViewFactory.CreateShape(shape);
	CreateShapePresenter(shape, view);

	m_onCreateView(view, m_shapes.size() - 1);
}

void CCanvasModel::InsertShape(size_t insertIndex, CShapeModelPtr & shape)
{
	CheckIndex(insertIndex, m_shapes.size());

	m_shapes.insert(
		m_shapes.begin() + insertIndex
		, shape
	);

	auto view = m_shapeViewFactory.CreateShape(shape);
	CreateShapePresenter(shape, view);

	m_onCreateView(view, insertIndex);
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

void CCanvasModel::CreateShapePresenter(CShapeModelPtr & pModel, CShapeViewPtr & pView)
{
	auto presenter = std::make_shared<CShapePresenter>(pModel);
	presenter->SetShapeView(pView.get());
	pView->SetPresenter(presenter);
}

std::vector<CShapeModelPtr>& CCanvasModel::GetShapes()
{
	return m_shapes;
}

void CCanvasModel::SetShapes(std::vector<CShapeModelPtr> & shapes)
{
	for (auto & shape : shapes)
	{
		PushBackShape(shape);
	}
}

IShapeCollection & CCanvasModel::GetShapeCollection()
{
	return *this;
}

IShapeProvider & CCanvasModel::GetShapeProvider()
{
	return *this;
}

void CCanvasModel::DeleteShape(size_t index)
{
	if (m_shapes.size() == 0)
	{
		throw std::runtime_error("Index out range");
	}
	CheckIndex(index, m_shapes.size() - 1);
	m_onDeleteView(index);
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
	for (size_t index = 0; index < m_shapes.size(); ++index)
	{
		DeleteShape(index);
	}
}

signal::Connection CCanvasModel::DoOnCreateView(std::function<void(const CShapeViewPtr&, size_t)> const & action)
{
	return m_onCreateView.connect(action);
}

signal::Connection CCanvasModel::DoOnDeleteView(std::function<void(size_t)> const & action)
{
	return m_onDeleteView.connect(action);
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
			const auto pPicture = dynamic_cast<CPictureModel*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return shape;
			}
		}
	}
	return CShapeModelPtr();
}


size_t CCanvasModel::GetShapeIndex(const CShapeModelPtr &  pShape) const
{
	return std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();
}


