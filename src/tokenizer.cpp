#include "tokenizer.hpp"

#include <iostream>

Tokenizer::Tokenizer(const std::string& buf) : buf(buf) {
}

char Tokenizer::charAt(size_t p) {
	if (p >= buf.size()) {
		return ' ';
	}
	return buf[p];
}

std::string Tokenizer::getNextToken() {
	if (pos >= buf.size()) {
		return "";
	}
	std::string delimiters[] = {
		" ", "\t", "//", "/*", "*/"
	};
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

size_t Tokenizer::getPos() const {
	return pos;
}

void Tokenizer::setPos(size_t p) {
	pos = p;
}