#include "line.hpp"

#include "tokenizer.hpp"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

Line::Line(const std::string& buf, bool waitForEndComment) : oldBuf(buf), indent(0), beginScope(false),
beginComment(waitForEndComment) {
	boost::trim_right(oldBuf);
	if (isEmpty()) {
		newBuf << "\n";
		return;
	}
	if (waitForEndComment) {
		auto pos = buf.find("*/");
		if (pos == std::string::npos) {
			newBuf << oldBuf;
		} else {
			commentAtBeginning = oldBuf.substr(0, pos+2);
		}
		beginComment = false;
		return;
	}
	std::string comment;
	bool addParenthesis = false;
	bool isFunction = true;
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
			if (token == "include" || token == "import") {
				auto file = tokenizer.getNextWord();
				auto param = tokenizer.getNextWord();
				std::stringstream* stream = &newBuf;
				if (param == "header") {
					stream = &headerBuf;
					newBuf.str("");
				} else if (param == "forward") {
					headerBuf << "class " << file << ";\n";
				}
				stream->seekp(0);
				if (token == "include") {
					*stream << "#include <" << file << ">";
				} else {
					if (file.find('.') == std::string::npos) {
						*stream << "#include \"" << file << ".hpp\"";
					} else {
						*stream << "#include \"" << file << "\"";
					}
				}
				*stream << "\n";
				return;
			} else if (token == "if" || token == "for" || token == "while") {
				isFunction = false;
				insertAfterSpace = "(";
				addParenthesis = true;
			}
		}
	}
	if (newBuf.str().back() == ':') {
		newBuf.seekp(-1, std::ios_base::end);
		if (isFunction) {
			// add declaration to header file
			newBuf << ";"; // overwrites ":"
			headerBuf << newBuf.str() << "\n";
			newBuf.seekp(-1, std::ios_base::end);
		}
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
	newBuf << spaceBuf << comment << "\n";
}

bool Line::isEmpty() const {
	return oldBuf.empty();
}

int Line::getIndent() const {
	return indent;
}

std::string Line::getNewBuf() const {
	return commentAtBeginning + newBuf.str();
}

std::string Line::getHeaderBuf() const {
	return headerBuf.str();
}

bool Line::isBeginScope() const {
	return beginScope;
}

bool Line::isBeginComment() const {
	return beginComment;
}
