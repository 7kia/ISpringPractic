#pragma once

class CRectangle;
class CEllipse;
class CTriangle;

// TODO : fix accepter
class IRenderShape
{
public:
	virtual ~IRenderShape() = default;

	virtual void Render(const CRectangle & shape) = 0;
	virtual void Render(const CEllipse & shape) = 0;
	virtual void Render(const CTriangle & shape) = 0;
};