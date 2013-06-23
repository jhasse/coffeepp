#pragma once

#include "../src/file.hpp"

#define BOOST_TEST_MODULE CoffeeppTest
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>

void checkCompiler(const std::string& cfpp, const std::string& cpp) {
	std::istringstream sstream{cfpp};
	File tmp(sstream);
	BOOST_CHECK_EQUAL(tmp.getNewBuf(), cpp);
}