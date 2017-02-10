#include "stdafx.h"
#include "ShapeLayer.h"

CShapeLayer::CShapeLayer()
{
}

void CShapeLayer::PushBackShapeData(CShapeDataPtr data)
{
	m_shapesData.push_back(data);
}

void CShapeLayer::InsertBackShapeData(CShapeDataPtr data, size_t index)
{
	m_shapesData.insert(m_shapesData.begin() + index, data);
}

CShapeDataPtr CShapeLayer::GetShapeData(size_t index)
{
	return m_shapesData[index];
}

CShapeDataPtr CShapeLayer::GetBackShapeData() const
{
	return m_shapesData[m_shapesData.size() - 1];
}

void CShapeLayer::PushBackShapePreseneter(CShapePresenterPtr data)
{
	m_shapePresenters.push_back(data);
}

void CShapeLayer::InsertBackShapeData(CShapePresenterPtr data, size_t index)
{
	m_shapePresenters.insert(m_shapePresenters.begin() + index, data);
}

CShapePresenterPtr CShapeLayer::GetShapePreseneter(size_t index)
{
	return m_shapePresenters[index];
}

CShapePresenterPtr CShapeLayer::GetBackShapePreseneter() const
{
	return m_shapePresenters[m_shapePresenters.size() - 1];
}

CShapePresenterPtr CShapeLayer::GetShapePreseneter(Vec2f position)
{
	CShapePresenterPtr result;

	for (auto iter = m_shapePresenters.begin(); iter != m_shapePresenters.end(); ++iter)
	{

		if ((*iter)->CheckPointIntersection(position))
		{
			result = *iter;
			break;
		}
	}

	return result;
}


std::vector<CShapeDataPtr>& CShapeLayer::GetShapesData()
{
	return m_shapesData;
}

std::vector<CShapePresenterPtr>& CShapeLayer::GetShapePresenters()
{
	return m_shapePresenters;
}

void CShapeLayer::DeleteShape(CShapePresenterPtr pShape)
{
	// TODO : the code might will be need to other place
	size_t deleteIndex = std::find(m_shapePresenters.begin(), m_shapePresenters.end(), pShape) - m_shapePresenters.begin();

	m_shapePresenters.erase(m_shapePresenters.begin() + deleteIndex);
	m_shapesData.erase(m_shapesData.begin() + deleteIndex);
}

void CShapeLayer::DeleteLastShape()
{
	m_shapePresenters.pop_back();
	m_shapesData.pop_back();
}