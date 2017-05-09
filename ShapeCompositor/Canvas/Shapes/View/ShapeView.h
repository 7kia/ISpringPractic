#pragma once


#include <memory>
#include "../IShape.h"
#include "../Model/ShapeModel.h"

class CShapePresenter;

// Mixin for avoid dublicate
class CShapeView 
	: public IShape
	, public CFrame
{
public:
	CShapeView(
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE,
		const Color & fillColor = DEFAULT_FILL_COLOR,
		const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
		const float outlineThikness = 1.f
	);
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
	void UpdateSelectedFrame(const CFrame & data);
	signal::Connection DoOnUpdateSelectedShape(std::function<void(const CFrame&)> const & action);
	void DoUnselected();

	virtual void Accept(IShapeVisitor & visitor) const = 0;

	virtual bool IsPointIntersection(const Vec2f point) const;

	void SetPresenter(std::shared_ptr<CShapePresenter> & pPresenter);


	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Color m_fillColor;
	Color m_outlineColor;
	float m_outlineThikness = 1.f;

	bool m_isSelected = false;

	signal::Signal<void(const CFrame&)> m_onUpdateSelectedShape;// For send message for selected shape
	signal::Connection m_connection;// For disconnect from selected shape
	std::shared_ptr<CShapePresenter> m_pPresenter;
};

using CShapeViewPtr = std::shared_ptr<CShapeView>;

bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapeModelPtr> & shapes);
