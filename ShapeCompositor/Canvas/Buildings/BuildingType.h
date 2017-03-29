#pragma once

#include <string>

#include "Canvas\Shapes\CShape.h"

class CBuildingType
{
public:
	CBuildingType();

	// TODO : fix style
	enum class Type
	{
		House = 0
		, Amount
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void			SetName(const std::string & name);
	std::string		GetName() const;


	void			SetSize(const SSize & size);
	SSize			GetSize() const;

	void			SetTexture(ID2D1Bitmap * pTexture);
	ID2D1Bitmap *	GetTexture() const;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::string m_name;
	SSize		m_size;
	ID2D1Bitmap * m_pTexture = nullptr;

};