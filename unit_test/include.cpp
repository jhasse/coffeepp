#include "check.hpp"

BOOST_AUTO_TEST_CASE(IncludeTest) {
	checkCompiler("Basic.cf++", R"(include iostream
import legacy.h
import Foo
import Bar header
import FooBar forward
)", R"(#pragma once

#include "Bar.hpp"
class FooBar;
)", R"(#include "Basic.hpp"

#include <iostream>
#include "legacy.h"
#include "Foo.hpp"
#include "FooBar.hpp"
)");

	// ignore whitespace
	checkCompiler("Whitespace.cf++", R"(include  	  asd
)", R"(#pragma once

)", R"(#include "Whitespace.hpp"

#include <asd>
)");
}
