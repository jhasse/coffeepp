#include "line.hpp"

#include "tokenizer.hpp"
#include "IndentionType.hpp"

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <vector>

Line::Line(const std::string& buf, const bool waitForEndComment, const bool wasBeginScope,
           boost::optional<IndentionType>& indentionType)
: oldBuf(buf), indent(0), beginScope(false), beginComment(waitForEndComment) {
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
	bool isFor = false;
	Tokenizer tokenizer(oldBuf);
	size_t pos = 0;
	bool emptyLine = true;
	std::string token;
	std::string spaceBuf;
	std::string insertAfterSpace;
	while (!(token = tokenizer.getNextToken()).empty()) {
		if (token == ",") {
			const auto next = tokenizer.peakNextSignificantToken();
			if (next == ")" || next == "}" || next == ">") {
				continue;
			}
		}
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
			if (isFor && token == "in") {
				token = ":";
			}
			if (token == ":=") {
				// Prepend auto:
				newBuf.seekg(-2, std::ios_base::end);
				std::vector<char> delims{' ', '\t', '('};
				bool finished = false;
				while (newBuf) {
					for (size_t i = 0; i < delims.size(); ++i) {
						if (static_cast<char>(newBuf.get()) == delims[i]) {
							finished = true;
							break;
						}
						newBuf.unget();
					}
					if (finished) {
						break;
					}
					newBuf.seekg(-1, std::ios_base::cur);
				}
				auto oldLength = newBuf.tellp();
				newBuf.seekp(newBuf.tellg());
				auto tmp = newBuf.str().substr(newBuf.tellg(), oldLength - newBuf.tellp());
				newBuf << "auto " << tmp;
				token = "=";
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
				if (token == "for") {
					isFor = true;
				}
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
	} else if (boost::trim_copy(buf) != "}" && !emptyLine) {
		newBuf << ';';
	}
	if (emptyLine) {
		oldBuf = "";
	}
	if (!indentionType && wasBeginScope && !oldBuf.empty()) {
		// We don't know yet, if the file uses tabs or spaces for indention. Let's see:
		auto it = oldBuf.begin();
		if (*it == '\t') {
			indentionType = IndentionType{};
		} else if (*it == ' ') {
			IndentionType tmp;
			tmp.tab = false;
			tmp.number = 0;
			do {
				++it;
				++tmp.number;
			} while (it != oldBuf.end() && *it == ' ');
			indentionType = tmp;
		}
	}
	if (indentionType) {
		while (oldBuf[indent] == (indentionType->tab ? '\t' : ' ')) {
			++indent;
		}
		indent /= indentionType->number;
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
