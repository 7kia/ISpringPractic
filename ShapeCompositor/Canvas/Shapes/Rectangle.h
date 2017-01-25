#pragma once

#include "CShape.h"


class IRectangle
{
public:
	virtual ~IRectangle() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void				SetWidth(float width) = 0;
	virtual float				GetWidth() const = 0;

	virtual void				SetHeight(float height) = 0;
	virtual float				GetHeight() const = 0;
};


class CRectangle
	: public IRectangle
{
public:
	CRectangle();
	CRectangle(SSize size);
	CRectangle(float width, float height);

	virtual ~CRectangle() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void				SetWidth(float width);
	float				GetWidth() const;

	void				SetHeight(float height);
	float				GetHeight() const;
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	float				m_width = 0.f;
	float				m_height = 0.f;
	//////////////////////////////////////////////////////////////////////


};
