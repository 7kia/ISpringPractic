// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


/*

	Заготовка

*/

BOOST_AUTO_TEST_SUITE(Test_suite)

struct Lexer_
{

};
BOOST_FIXTURE_TEST_SUITE(Lexer, Lexer_)
	// Заготовка
	BOOST_AUTO_TEST_CASE(Check_on_empty_vector)
	{
		BOOST_CHECK(true);
	}
BOOST_AUTO_TEST_SUITE_END()// Lexer_

BOOST_AUTO_TEST_SUITE_END()// Test_suite