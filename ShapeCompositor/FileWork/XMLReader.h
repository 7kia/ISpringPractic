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

#include "Canvas\CanvasModel.h"
#include "Canvas\Picture\PictureView.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include <string>

class CXMLReader
{
public:
	CXMLReader() = default;

	struct ReadData
	{
		ReadData();
		ReadData(
			std::vector<CShapeViewPtr> & shapeData,
			CTextureStorage & textureStorage
		);
		std::vector<CShapeViewPtr> shapeData;
		CTextureStorage textureStorage;
	};

	struct DataForCreation
	{
		DataForCreation(
			const CShapeViewFactory & shapeFactory,
			CD2DImageFactory & imageFactory
		);
		const CShapeViewFactory & shapeFactory;
		CD2DImageFactory & imageFactory;
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	static bool Save(
		const std::wstring & path,
		const std::vector<CShapeViewPtr>  & shapes,
		const CTextureStorage & textureStorage
	);
	static ReadData Open(
		const std::wstring & path,
		DataForCreation & dataForCreation
	);	
};