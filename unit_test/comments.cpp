
void test() {
	checkCompiler(
R"(int main():
	auto a = 5 // setting a
	/* if while for */int b = 3// setting b
	if/**/ a==3/**/: //:
		/*something*/)",
R"(int main() {
	auto a = 5; // setting a
	/* if while for */int b = 3;// setting b
	if/**/ (a==3)/**/ { //:
		/*something*/
	}
})");
}