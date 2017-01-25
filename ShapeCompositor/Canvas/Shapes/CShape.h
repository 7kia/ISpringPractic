#pragma once

#include "IShape.h"

class CShape : public IShape
{
public:
	CShape();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	// Position
	void SetPosition(D2D1_POINT_2F position) override;
	D2D1_POINT_2F GetPosition() const override;
	// Inner Color
	void SetInnerColor(D2D1_COLOR_F color) override;
	D2D1_COLOR_F GetInnerColor() const override;
	// Outer Color
	void SetOuterColor(D2D1_COLOR_F color) override;
	D2D1_COLOR_F GetOuterColor() const override;

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	D2D1_POINT_2F m_position;
	D2D1_COLOR_F m_innerColor;
	D2D1_COLOR_F m_outerColor;
};