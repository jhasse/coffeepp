#include "check.hpp"

BOOST_AUTO_TEST_CASE(CommaTest) {
	checkCompiler("Comma.cf++", R"(include cstdio

int main():
	printf("foo",)
)", R"(#pragma once

int main();
)", R"(#include "Comma.hpp"

#include <cstdio>

int main() {
	printf("foo");
}
)");
}
