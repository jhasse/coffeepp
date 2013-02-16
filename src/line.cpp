#include "line.hpp"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

Line::Line(const std::string& buf, bool waitForEndComment) : oldBuf(buf), indent(0), beginScope(false),
beginComment(waitForEndComment) {
	boost::trim_right(oldBuf);
	if (isEmpty()) {
		return;
	}
	if (waitForEndComment) {
		auto pos = buf.find("*/");
		if (pos == std::string::npos) {
			newBuf << oldBuf;
		} else {
			newBuf << oldBuf.substr(0, pos+2);
		}
		beginComment = false;
		return;
	}
	while (oldBuf[indent] == '\t') {
		++indent;
	}
	std::string comment;
	bool addParenthesis = false;
	std::stringstream sstream(oldBuf);
	size_t pos = 0;
	while (sstream) {
		std::string token;
		sstream >> token;
		if (token == "/*") {
			beginComment = true;
		}
		if (token == "//" || token == "/*") {
			comment = oldBuf.substr(pos);
			break;
		}
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
	if (newBuf.str().back() == ':') {
		newBuf.seekp(-1, std::ios_base::end);
		if (addParenthesis) {
			newBuf << ")";
		}
		newBuf << " {";
		beginScope = true;
	} else if (newBuf.str().back() != '}' && !newBuf.str().empty()) {
		newBuf << ';';
	}
	newBuf << comment;
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

bool Line::isBeginComment() const {
	return beginComment;
}