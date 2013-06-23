#include "line.hpp"

#include "tokenizer.hpp"

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
			comment = oldBuf.substr(0, pos+2);
		}
		beginComment = false;
		return;
	}
	std::string comment;
	bool addParenthesis = false;
	Tokenizer tokenizer(oldBuf);
	size_t pos = 0;
	bool emptyLine = true;
	std::string token;
	std::string spaceBuf;
	std::string insertAfterSpace;
	while (!(token = tokenizer.getNextToken()).empty()) {
		if (token == "/*") {
			// Search for the end
			auto endPos = oldBuf.find("*/", tokenizer.getPos());
			if (endPos == std::string::npos) {
				beginComment = true;
				comment = oldBuf.substr(pos);
				break;
			} else {
				spaceBuf += oldBuf.substr(pos, endPos + 2 - pos);
				pos = endPos + 2;
				tokenizer.setPos(pos);
				continue;
			}
		}
		if (token == "//") {
			comment = oldBuf.substr(pos);
			break;
		}
		if (emptyLine && token != " " && token != "\t") {
			emptyLine = false;
		}
		pos = tokenizer.getPos();
		if (token == " " || token == "\t") {
			spaceBuf += token;
		} else {
			if (!spaceBuf.empty()) {
				spaceBuf += insertAfterSpace;
				insertAfterSpace = "";
			}
			newBuf << spaceBuf << token;
			spaceBuf = "";
			if (token == "include") {
				std::string file;
				tokenizer.getNextToken(); // space
				file = tokenizer.getNextToken();
				newBuf.seekp(0);
				newBuf << "#include <" << file << ">";
				return;
			} else if (token == "if" || token == "for" || token == "while") {
				insertAfterSpace = "(";
				addParenthesis = true;
			}
		}
	}
	if (newBuf.str().back() == ':') {
		newBuf.seekp(-1, std::ios_base::end);
		if (addParenthesis) {
			newBuf << ")";
		}
		newBuf << " {";
		beginScope = true;
	} else if (newBuf.str().back() != '}' && !emptyLine) {
		newBuf << ';';
	}
	if (emptyLine) {
		oldBuf = "";
	}
	while (oldBuf[indent] == '\t') {
		++indent;
	}
	newBuf << spaceBuf << comment;
}

bool Line::isEmpty() const {
	return oldBuf.empty();
}

int Line::getIndent() const {
	return indent;
}

std::string Line::getNewBuf() const {
	return comment + newBuf.str();
}

bool Line::isBeginScope() const {
	return beginScope;
}

bool Line::isBeginComment() const {
	return beginComment;
}