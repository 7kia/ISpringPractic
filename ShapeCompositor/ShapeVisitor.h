#pragma once

class CRectangle;
class CEllipse;
class CTriangle;
class CBuilding;// TODO : see need transfer ?

class IShapeVisitor
{
public:
	virtual ~IShapeVisitor() = default;

	virtual void Visit(const CRectangle & shape) = 0;
	virtual void Visit(const CEllipse & shape) = 0;
	virtual void Visit(const CTriangle & shape) = 0;
	virtual void Visit(const CBuilding & shape) = 0;

};