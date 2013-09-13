#include "check.hpp"

BOOST_AUTO_TEST_CASE(ForTest) {
	checkCompiler("For.cf++", R"(include iostream
include vector

int main():
	numbers := std::vector<int>{1, 2, 3, 4, 5}
	for int number in numbers:
		std::cout << number << std::endl
)", R"(#pragma once

int main();
)", R"(#include "For.hpp"

#include <iostream>
#include <vector>

int main() {
	auto numbers = std::vector<int>{1, 2, 3, 4, 5};
	for (int number : numbers) {
		std::cout << number << std::endl;
	}
}
)");
}
