#include "check.hpp"

#include <iostream>
#include <sstream>

void checkCompiler(const std::string& filename,
                   const std::string& cfpp,
                   const std::string& hpp,
                   const std::string& cpp) {
	std::istringstream sstream{cfpp};
	File tmp(sstream, filename);
	BOOST_CHECK_EQUAL(tmp.getNewBuf(), cpp);
	BOOST_CHECK_EQUAL(tmp.getHeaderBuf(), hpp);
}
