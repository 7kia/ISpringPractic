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

	void			SetTextureName(const std::string & textureName);
	std::string		GetTextureName() const;

	void			SetSize(const SSize & size);
	SSize			GetSize() const;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::string m_name;
	SSize		m_size;
	std::string m_textureName;

	// TODO : add data
};