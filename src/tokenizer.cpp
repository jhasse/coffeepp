#include "tokenizer.hpp"

#include <iostream>
#include <array>

Tokenizer::Tokenizer(const std::string& buf) : buf(buf) {
}

char Tokenizer::charAt(size_t p) {
	if (p >= buf.size()) {
		return ' ';
	}
	return buf[p];
}

const std::array<std::string, 6> delimiters = {{
	" ", "\t", "//", "/*", "*/", ","
}};

std::string Tokenizer::getNextToken() {
	if (pos >= buf.size()) {
		return "";
	}
	std::string token;
	while (true) {
		for (auto delim : delimiters) {
			bool match = true;
			for (size_t i = 0; i < delim.size(); ++i) {
				if (charAt(pos + i) != delim[i]) {
					match = false;
					break;
				}
			}
			if (match) {
				if (token.empty()) {
					pos += delim.size();
					return delim;
				} else {
					return token;
				}
			}
		}
		token += charAt(pos);
		++pos;
	}
}

std::string Tokenizer::getNextWord() {
	std::string t;
	do {
		t = getNextToken();
	} while ((t == " " || t == "\t") && t != "");
	return t;
}

std::string Tokenizer::peakNextSignificantToken() {
	auto oldPos = pos;
	std::string token;
	while((token = getNextToken()) != "") {
		bool found = false;
		for (const auto& d : delimiters) {
			if (d == token) {
				found = true;
				break;
			}
		}
		if (!found) {
			break;
		}
	}
	pos = oldPos;
	return token;
}

size_t Tokenizer::getPos() const {
	return pos;
}

void Tokenizer::setPos(size_t p) {
	pos = p;
}
