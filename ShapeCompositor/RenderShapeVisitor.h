#pragma once

class CRectangleShapeData;
class CEllipseDataShape;
class CTriangleShapeData;

class IRenderShapeVisitor
{
public:
	virtual ~IRenderShapeVisitor() = default;

	virtual void Visit(const CRectangleShapeData & shape) = 0;
	virtual void Visit(const CEllipseDataShape & shape) = 0;
	virtual void Visit(const CTriangleShapeData & shape) = 0;

};