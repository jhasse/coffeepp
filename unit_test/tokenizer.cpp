#include "../src/tokenizer.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TokenizerTest) {
	Tokenizer t("Hello World\tthis/*is*/the//end");
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
	BOOST_CHECK_EQUAL(t.getNextToken(), "");
}