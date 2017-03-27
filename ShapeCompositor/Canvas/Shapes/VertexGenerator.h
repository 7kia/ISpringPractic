#pragma once

#include "AllShapes.h"

class CVertexGenerator 
	: public IShapeVisitor
{
public:
	using ListVerteces = std::vector<Vec2f>;

	ListVerteces GetVertices(const IShape & shape);

	void Visit(const CRectangle & shape) override;
	void Visit(const CEllipse & shape) override;
	void Visit(const CTriangle & shape) override;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ListVerteces m_generatedVerteces;
};