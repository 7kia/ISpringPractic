#pragma once

class CRectangleView;
class CEllipseView;
class CTriangleView;
class CPictureView;

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() = default;

	virtual void Visit(const CRectangleView & shape) = 0;
	virtual void Visit(const CEllipseView & shape) = 0;
	virtual void Visit(const CTriangleView & shape) = 0;
	virtual void Visit(const CPictureView & shape) = 0;
};