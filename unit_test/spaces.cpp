#include "check.hpp"

BOOST_AUTO_TEST_CASE(SpacesTest) {
	checkCompiler("main.cf++", R"(include stdio.h

int main():
  puts("hi")
  return 0
)", R"(#pragma once

int main();
)", R"(#include "main.hpp"

#include <stdio.h>

int main() {
  puts("hi");
  return 0;
}
)");
	checkCompiler("main.cf++", R"(int main():
  if false:
    return 1
  return 0
)", R"(#pragma once

int main();
)", R"(#include "main.hpp"

int main() {
  if (false) {
    return 1;
  }
  return 0;
}
)");
}
