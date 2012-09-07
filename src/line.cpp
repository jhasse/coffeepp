#include "line.hpp"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

Line::Line(const std::string& buf) : oldBuf(buf), indent(0), beginScope(false) {
	boost::trim_right(oldBuf);
	if (isEmpty()) {
		return;
	}
	while (oldBuf[indent] == '\t') {
		++indent;
		newBuf << '\t';
	}
	bool addParenthesis = false;
	std::stringstream sstream(oldBuf);
	size_t pos = 0;
	while (sstream) {
		std::string token;
		sstream >> token;
		newBuf << oldBuf.substr(pos, static_cast<size_t>(sstream.tellg())-pos);
		pos = static_cast<size_t>(sstream.tellg());
		if (token == "include") {
			std::string file;
			sstream >> file;
			newBuf.seekp(0);
			newBuf << "#include <" << file << ">";
			return;
		} else if (token == "if" || token == "for" || token == "while") {
			newBuf << " (";
			sstream.ignore(1);
			++pos;
			addParenthesis = true;
		}
	}
	if (oldBuf.back() == ':') {
		newBuf.seekp(-1, std::ios_base::end);
		if (addParenthesis) {
			newBuf << ")";
		}
		newBuf << " {";
		beginScope = true;
	} else if (oldBuf.back() != '}') {
		newBuf << ';';
	}
}

bool Line::isEmpty() const {
	return oldBuf.empty();
}

int Line::getIndent() const {
	return indent;
}

std::string Line::getNewBuf() const {
	return newBuf.str();
}

bool Line::isBeginScope() const {
	return beginScope;
}