#include "stdafx.h"
#include "XMLReader.h"

using namespace boost::filesystem;

namespace fs = boost::filesystem;
using fs::path;


namespace
{
	std::string GetShapeName(ShapeType type)
	{
		switch (type)
		{
		case ShapeType::Triangle:
			return "Triangle";
		case ShapeType::Rectangle:
			return "Rectangle";
		case ShapeType::Ellipse:
			return "Ellipse";
		case ShapeType::Picture:
			return "Picture";
		default:
			throw std::runtime_error("Incorrect shape type");
			break;
		}
		return "Triangle";
	}

	ShapeType GetShapeType(std::string const& typeStr)
	{
		if (typeStr == "Triangle")
		{
			return ShapeType::Triangle;
		}
		else if (typeStr == "Rectangle")
		{
			return ShapeType::Rectangle;
		}
		else if (typeStr == "Ellipse")
		{
			return ShapeType::Ellipse;
		}
		else if (typeStr == "Picture")
		{
			return ShapeType::Picture;
		}
		else
		{
			throw std::runtime_error("Incorrect shape type");
		}
	}

	std::string ToString(const std::wstring& str)
	{
		return std::string(str.begin(), str.end());
	}
	std::wstring ToWString(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}

}

bool CXMLReader::Save(
	const std::wstring & path,
	const std::vector<CShapeModel> & shapes,
	const CTextureStorage & textureStorage
)
{
	if (path.empty())
	{
		return false;
	}
	try
	{
		boost::property_tree::ptree propertyTree;
		if (shapes.size() == 0)
		{
			boost::property_tree::ptree child;
			propertyTree.add_child("Shapes", child);
		}
		for (auto &shape : shapes)
		{
			boost::property_tree::ptree child;
			child.add("Type", GetShapeName(shape->GetType()));
			child.add("X", std::to_string(shape->GetPosition().x));
			child.add("Y", std::to_string(shape->GetPosition().y));
			child.add("Width", std::to_string(shape->GetSize().width));
			child.add("Height", std::to_string(shape->GetSize().height));

			if (shape->GetType() == ShapeType::Picture)
			{
				// not wstring because not << overload for wstring
				const auto pictureModel = dynamic_cast<CPictureModel*>(shape.get());
				child.add("Texture", ToString(textureStorage.GetNameTexture(pictureModel->GetTexture())) );
			}

			propertyTree.add_child("Shapes.Shape", child);
		}
		std::stringstream stream;
		boost::property_tree::write_xml(stream, propertyTree);

		std::ofstream out(path);
		std::string str;
		while (!stream.eof())
		{
			stream >> str;
			out << str;
		}
		out.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
	return false;
}

CXMLReader::ReadData CXMLReader::Open(
	const std::wstring & path,
	DataForCreation & dataForCreation
)
{
	if (path.empty())
	{
		return ReadData();
	}
	try
	{
		ReadData readData;
		std::ifstream stream(path);
		auto folder = fs::path(path).parent_path().generic_string() + "/" + fs::path(path).stem().generic_string();


		boost::property_tree::ptree propertyTree;
		boost::property_tree::read_xml(stream, propertyTree);

		for (auto &shape : propertyTree.get_child("Shapes"))
		{
			if (shape.first == "Shape")
			{
				std::string type = shape.second.get<std::string>("Type");
				float x = shape.second.get<float>("X");
				float y = shape.second.get<float>("Y");
				float width = shape.second.get<float>("Width");
				float height = shape.second.get<float>("Height");

				CShapeModel data;
				data.type = GetShapeType(type);
				data.position = Vec2f(x, y);
				data.size = SSize(width, height);

				if (type == "Picture")
				{
					std::string texture = shape.second.get<std::string>("Texture");
					readData.textureStorage.AddTexture(
						ToWString(texture),
						dataForCreation.imageFactory.CreateTexture(ToWString(folder + "/" + texture))
					);
					readData.shapeData.push_back(
						CPictureModel(
							readData.textureStorage.GetTexture(ToWString(texture)),
							data.position,
							data.size
						)
					);
				}
				else
				{
					readData.shapeData.push_back(data);
				}
			}
		}

		if (!exists(folder) && readData.textureStorage.GetCount())
		{
			throw std::runtime_error("Not directory for open file");
		}

		stream.close();
		return readData;
	}
	catch (boost::property_tree::xml_parser_error e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}

	return ReadData();
}

CXMLReader::ReadData::ReadData()
	: textureStorage(CanvasNamespace::MAX_PICTURE_SIZE)
{
}

CXMLReader::ReadData::ReadData(
	std::vector<CShapeViewPtr>& shapeData,
	CTextureStorage & textureStorage
)
	: shapeData(shapeData)
	, textureStorage(textureStorage)
{
}


CXMLReader::DataForCreation::DataForCreation(
	const CShapeViewFactory & shapeFactory,
	CD2DImageFactory & imageFactory
)
	: shapeFactory(shapeFactory)
	, imageFactory(imageFactory)
{
}
