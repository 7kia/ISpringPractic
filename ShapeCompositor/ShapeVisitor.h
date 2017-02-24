#pragma once

class CRectangle;
class CEllipse;
class CTriangle;

// TODO : fix accepter
class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() = default;

	virtual void Visit(const CRectangle & shape) = 0;
	virtual void Visit(const CEllipse & shape) = 0;
	virtual void Visit(const CTriangle & shape) = 0;
};