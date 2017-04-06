#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

#include "Canvas\Canvas.h"


class CXMLReader
{
public:
	CXMLReader();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	static bool Save(const std::wstring path, std::vector<CShapePtr> const& shapes);
	static bool Open(
		const std::wstring path
		, CCanvas & canvas
		, const CShapeFactory & factory
	);	
};