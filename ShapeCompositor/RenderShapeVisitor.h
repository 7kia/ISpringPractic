#pragma once

class CRectangleView;
class CEllipseView;
class CTriangleView;

// TODO : fix accepter
class IRenderShape
{
public:
	virtual ~IRenderShape() = default;

	virtual void Visit(const CRectangleView & shape) = 0;
	virtual void Visit(const CEllipseView & shape) = 0;
	virtual void Visit(const CTriangleView & shape) = 0;
};