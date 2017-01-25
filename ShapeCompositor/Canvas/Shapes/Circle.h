#pragma once

#include "CShape.h"

class ICircle
{
public:
	virtual ~ICircle() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void SetRadius(float value) = 0;
	virtual float GetRadius() const = 0;

};

class CCircle
	: public ICircle
{
public:
	CCircle();
	CCircle(float radius);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetRadius(float value) override;
	float GetRadius() const override;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	float	m_radius = 0.f;
};