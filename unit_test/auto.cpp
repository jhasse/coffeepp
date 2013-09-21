#include "check.hpp"

BOOST_AUTO_TEST_CASE(AutoTest) {
	checkCompiler("Auto.cf++", R"(int main():
	a := 123
	const b := 456
	for i := 0; i < 10; ++i:
		b -= a
)", R"(#pragma once

int main();
)", R"(#include "Auto.hpp"

int main() {
	auto a = 123;
	const auto b = 456;
	for (auto i = 0; i < 10; ++i) {
		b -= a;
	}
}
)");
}
