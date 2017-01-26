#pragma once

class CRectangleShape;
class CEllipseShape;
class CTriangleShape;

class IRenderShapeVisitor
{
public:
	virtual ~IRenderShapeVisitor() = default;

	virtual void Visit(const CRectangleShape & shape) = 0;
	virtual void Visit(const CEllipseShape & shape) = 0;
	virtual void Visit(const CTriangleShape & shape) = 0;

};