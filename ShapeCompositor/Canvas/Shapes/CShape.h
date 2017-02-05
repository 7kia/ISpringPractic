#pragma once


#include <memory>
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(
		const Vec2f position
		, const SSize size
		, const Color fillColor
		, const Color outlineColor
	);
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
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
public:

protected:
	Vec2f m_position;

	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;

};

using PCShape = std::shared_ptr<CShape>;