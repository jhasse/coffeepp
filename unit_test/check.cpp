#include "check.hpp"

#include <iostream>
#include <sstream>

void checkCompiler(const std::string& cfpp, const std::string& cpp, const std::string& hpp) {
	std::istringstream sstream{cfpp};
	File tmp(sstream);
	BOOST_CHECK_EQUAL(tmp.getNewBuf(), cpp);
	BOOST_CHECK_EQUAL(tmp.getHeaderBuf(), hpp);
}