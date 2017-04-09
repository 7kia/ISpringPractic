#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>
#include <boost/filesystem.hpp>

#include "Canvas\Canvas.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include <string>

class CXMLReader
{
public:
	CXMLReader();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	static bool Save(
		const std::wstring path,
		std::vector<CShapePtr> const & shapes,
		const CTextureStorage & textureStorage
	);
	static bool Open(
		const std::wstring path,
		CCanvas & canvas,
		const CShapeFactory & factory,
		CTextureStorage & textureStorage,
		CD2DImageFactory & imageFactory// image require D2D draw
	);	
};