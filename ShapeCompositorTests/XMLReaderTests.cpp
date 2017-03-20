#include "stdafx.h"
#include "Canvas/Canvas.h"
#include "XMLREader/XMLREader.h"

BOOST_AUTO_TEST_SUITE(CXMLReader_suite)

struct XMLReaderFixture
{
	CXMLReader xmlReader;
	
	CCanvas emptyCanvas;
	CCanvas fullCanvas;
	CShapeFactory factory;

	CShapePtr ellipse;
	CShapePtr rectangle;
	CShapePtr triangle;

	XMLReaderFixture()
		: ellipse(factory.CreateShape(SShapeData(ShapeType::Ellipse)))
		, rectangle(factory.CreateShape(SShapeData(ShapeType::Rectangle)))
		, triangle(factory.CreateShape(SShapeData(ShapeType::Triangle)))
	{
		fullCanvas.PushBackShape(ellipse);
		fullCanvas.PushBackShape(triangle);
		fullCanvas.PushBackShape(rectangle);
	}
};
BOOST_FIXTURE_TEST_SUITE(XMLREader, XMLReaderFixture)

BOOST_AUTO_TEST_SUITE(Save)
	BOOST_AUTO_TEST_CASE(Empty_file)
	{
		BOOST_REQUIRE_NO_THROW(xmlReader.Save(L"Empty1.xml", emptyCanvas.GetShapes()));
	}
	BOOST_AUTO_TEST_CASE(Not_empty_file)
	{
		BOOST_REQUIRE_NO_THROW(xmlReader.Save(L"NotEmpty1.xml", fullCanvas.GetShapes()));
	}
BOOST_AUTO_TEST_SUITE_END()// Save

BOOST_AUTO_TEST_SUITE(Open)
	BOOST_AUTO_TEST_CASE(Empty_file)
	{
		BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 3);

		BOOST_REQUIRE_NO_THROW(xmlReader.Open(L"Empty1.xml", fullCanvas, factory));

		BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 0);
	}
	BOOST_AUTO_TEST_CASE(Not_empty_file)
	{
		BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 0);

		BOOST_REQUIRE_NO_THROW(xmlReader.Open(L"NotEmpty1.xml", emptyCanvas, factory));

		BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 3);
		BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), ellipse);
		BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), triangle);
		BOOST_CHECK_EQUAL(fullCanvas.GetShape(2), rectangle);
	}
BOOST_AUTO_TEST_SUITE_END()// Open


BOOST_AUTO_TEST_SUITE_END()// XMLReaderFixture


BOOST_AUTO_TEST_SUITE_END()// CXMLReader_suite