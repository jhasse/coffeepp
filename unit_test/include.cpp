#include "check.hpp"

BOOST_AUTO_TEST_CASE(IncludeTest) {
	checkCompiler(R"(
include iostream
import legacy.h
import Foo
import Bar header
import FooBar forward
)", R"(
#include <iostream>
#include "legacy.h"
#include "Foo.hpp"
#include "FooBar.hpp"
)", R"(#include "Bar.hpp"
class FooBar;
)");

	// ignore whitespace
	checkCompiler(R"(
include  	  asd
)", R"(
#include <asd>
)");
}