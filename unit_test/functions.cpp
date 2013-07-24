#include "check.hpp"

BOOST_AUTO_TEST_CASE(FunctionsTest) {
	checkCompiler("foobar.cf++",
R"(int foo(int asd):
	return asd
)",
R"(#pragma once

int foo(int asd);
)",
R"(#include "foobar.hpp"

int foo(int asd) {
	return asd;
}
)");
}
