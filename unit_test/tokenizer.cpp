#include "../src/tokenizer.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CoffeeppTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TokenizerTest) {
	std::string text = "Hello World\tthis/*is*/the//end\t  word ";
	Tokenizer t(text);
	BOOST_CHECK_EQUAL(t.getNextToken(), "Hello");
	BOOST_CHECK_EQUAL(t.getNextToken(), " ");
	BOOST_CHECK_EQUAL(t.getNextToken(), "World");
	BOOST_CHECK_EQUAL(t.getNextToken(), "\t");
	BOOST_CHECK_EQUAL(t.getNextToken(), "this");
	BOOST_CHECK_EQUAL(t.getNextToken(), "/*");
	BOOST_CHECK_EQUAL(t.getNextToken(), "is");
	BOOST_CHECK_EQUAL(t.getPos(), 20u);
	t.setPos(19);
	BOOST_CHECK_EQUAL(t.getNextToken(), "s");
	BOOST_CHECK_EQUAL(t.getNextToken(), "*/");
	BOOST_CHECK_EQUAL(t.getNextToken(), "the");
	BOOST_CHECK_EQUAL(t.getNextToken(), "//");
	BOOST_CHECK_EQUAL(t.getNextToken(), "end");
	BOOST_CHECK_EQUAL(t.getNextWord(), "word");
	BOOST_CHECK_EQUAL(t.getNextWord(), "");
	BOOST_CHECK_EQUAL(t.getNextToken(), "");
	text = "foo(bar,  )";
	Tokenizer t2(text);
	BOOST_CHECK_EQUAL(t2.getNextToken(), "foo(bar");
	BOOST_CHECK_EQUAL(t2.getNextToken(), ",");
	BOOST_CHECK_EQUAL(t2.peakNextSignificantToken(), ")");
	BOOST_CHECK_EQUAL(t2.getNextToken(), " ");
	BOOST_CHECK_EQUAL(t2.getNextToken(), " ");
	BOOST_CHECK_EQUAL(t2.getNextToken(), ")");
	BOOST_CHECK_EQUAL(t2.getNextToken(), "");
}
