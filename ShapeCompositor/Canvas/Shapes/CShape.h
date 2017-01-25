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
	void SetFillColor(Color color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(Color color) override;
	Color GetOutlineColor() const override;

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	Vec2f m_position;
	Color m_fillColor;
	Color m_outlineColor;
};

using PCShape = std::shared_ptr<CShape>;