#include "check.hpp"

BOOST_AUTO_TEST_CASE(CommentsTest) {
	checkCompiler(
R"(
int main():
	// if a == 3:
	if b == 4:
		return 0 // exit
)",
R"(
int main() {
	// if a == 3:
	if (b == 4) {
		return 0; // exit
	}
}
)");
	checkCompiler(
R"(
// int main():
	/* if donothing: */
)",
R"(
// int main():
	/* if donothing: */
)");
	checkCompiler(
R"(int main():
	auto a = 5 // setting a
	/* if while for */int b = 3//setting b
	if/**/ a==3/*ignore*/://x:
		int b = 3  /*something*/)",
R"(int main() {
	auto a = 5; // setting a
	/* if while for */int b = 3;//setting b
	if/**/ (a==3/*ignore*/) {//x:
		int b = 3;  /*something*/
	}
}
)");
}