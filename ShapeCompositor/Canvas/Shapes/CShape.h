#pragma once

#include <memory>

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
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	// Inner Color
	void SetInnerColor(Color color) override;
	Color GetInnerColor() const override;
	// Outer Color
	void SetOuterColor(Color color) override;
	Color GetOuterColor() const override;

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	Vec2f m_position;
	Color m_innerColor;
	Color m_outerColor;
};

using PCShape = std::unique_ptr<CShape>;