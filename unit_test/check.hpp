#pragma once

#include "../src/file.hpp"

#include <boost/test/unit_test.hpp>

void checkCompiler(const std::string& filename,
                   const std::string& cfpp,
                   const std::string& hpp,
                   const std::string& cpp);
