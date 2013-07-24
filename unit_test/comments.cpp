#include "check.hpp"

BOOST_AUTO_TEST_CASE(CommentsTest) {
	checkCompiler("Test.cf++", R"(int main():
	// if a == 3:
	if b == 4:
		return 0 // exit
)", R"(#pragma once

int main();
)", R"(#include "Test.hpp"

int main() {
	// if a == 3:
	if (b == 4) {
		return 0; // exit
	}
}
)");
	checkCompiler("Test.cf++",
R"(// int main():
	/* if donothing: */
)", R"(#pragma once

)", R"(#include "Test.hpp"

// int main():
	/* if donothing: */
)");
	checkCompiler("Test.cf++",
R"(int main():
	auto a = 5 // setting a
	/* if while for */int b = 3//setting b
	if/**/ a==3/*ignore*/://x:
		int b = 3  /*something*/)",
R"(#pragma once

int main();
)", R"(#include "Test.hpp"

int main() {
	auto a = 5; // setting a
	/* if while for */int b = 3;//setting b
	if/**/ (a==3/*ignore*/) {//x:
		int b = 3;  /*something*/
	}
}
)");
}
