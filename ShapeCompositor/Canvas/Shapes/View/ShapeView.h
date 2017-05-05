#pragma once


#include <memory>
#include "IShape.h"
#include "Model/ShapeModel.h"

// Mixin for avoid dublicate
class CShapeView 
	: public IShape
	, public CFrame
{
public:
	CShapeView(const ShapeType type);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	// Inner Color
	void SetFillColor(const Color &  color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(const Color &  color) override;
	Color GetOutlineColor() const override;
	// Thikness outline
	void SetOutlineThickness(const float thickness) override;
	float GetOutlineThickness() const override;

	//--------------------------------------------
	// IFrame
	void SetFrame(const CFrame & data) override;
	//--------------------------------------------
	virtual bool IsPointIntersection(const Vec2f point) const;

	void SetPresenter(CShapePresenter & presenter);

	signal::Connection DoOnRectChanged(std::function<void(const CFrame&)> const& action);

	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Color m_fillColor;
	Color m_outlineColor;
	float m_outlineThikness = 1.f;

	signal::Signal<void(CShapeModelPtr &, size_t)> m_onCreateView;
	signal::Signal<void(const CFrame&)> m_onChangeRect;// For send message for selected shape

	CShapePresenter m_presenter;
};

using CShapeViewPtr = std::shared_ptr<CShapeView>;