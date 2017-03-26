#pragma once

class CRectangle;
class CEllipse;
class CTriangle;
class CCanvas;

class IObjectVisitor
{
public:
	virtual ~IObjectVisitor() = default;

	virtual void Visit(const CRectangle & shape) = 0;
	virtual void Visit(const CEllipse & shape) = 0;
	virtual void Visit(const CTriangle & shape) = 0;
};