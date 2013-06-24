#pragma once

#include "../src/file.hpp"

#include <boost/test/unit_test.hpp>

void checkCompiler(const std::string& cfpp, const std::string& cpp, const std::string& hpp = "");