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


CXMLReader::CXMLReader()
{
}

bool CXMLReader::Save(
	const std::wstring path,
	std::vector<CShapePtr> const & shapes,
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
				const auto picture = dynamic_cast<CPicture*>(shape.get());
				child.add("Texture", ToString(textureStorage.GetNameTexture(picture->GetTexture())) );
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

bool CXMLReader::Open(
	const std::wstring path,
	CCanvas & canvas,
	const CShapeFactory & factory,
	CTextureStorage & textureStorage,
	CD2DImageFactory & imageFactory
)
{
	if (path.empty())
	{
		return false;
	}
	try
	{
		std::ifstream stream(path);
		auto folder = fs::path(path).stem().generic_string();

		if (!exists(folder) && textureStorage.GetCount())
		{
			throw std::runtime_error("Not directory for open file");
		}

		boost::property_tree::ptree propertyTree;
		boost::property_tree::read_xml(stream, propertyTree);

		std::vector<CShapePtr> shapesData;
		for (auto &shape : propertyTree.get_child("Shapes"))
		{
			if (shape.first == "Shape")
			{
				std::string type = shape.second.get<std::string>("Type");
				float x = shape.second.get<float>("X");
				float y = shape.second.get<float>("Y");
				float width = shape.second.get<float>("Width");
				float height = shape.second.get<float>("Height");

				SShapeData data;
				data.type = GetShapeType(type);
				data.position = Vec2f(x, y);
				data.size = SSize(width, height);

				if (type == "Picture")
				{
					std::string texture = shape.second.get<std::string>("Texture");
					textureStorage.AddTexture(ToWString(texture), imageFactory.CreateTexture(ToWString(folder + "/" + texture)));
					shapesData.push_back(std::make_shared<CPicture>(textureStorage.GetTexture(ToWString(texture)), data.position, data.size));
				}
				else
				{
					shapesData.push_back(factory.CreateShape(data));
				}
			}
		}

		canvas.Clear();
		canvas.SetShapes(shapesData);

		stream.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
	return false;
}
