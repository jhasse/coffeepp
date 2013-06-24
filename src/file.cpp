#include "file.hpp"

#include "line.hpp"

#include <fstream>
#include <iostream>

File::File(std::istream& in) : indent(0) {
	bool waitForEndComment = false;
	while (true) {
		std::string buf;
		std::getline(in, buf);
		if (!in) {
			break;
		}
		auto line = std::make_shared<Line>(buf, waitForEndComment);
		while (!waitForEndComment && line->getIndent() > indent) {
			++indent;
		}
		if (line->isBeginComment() || waitForEndComment) {
			waitForEndComment = true;
		} else {
			closeScopes(line->getIndent());
		}
		lines.push_back(line);
	}
	closeScopes(0);
}

std::string File::getNewBuf() const {
	std::string buf;
	for (const auto& line : lines) {
		buf += line->getNewBuf();
	}
	return buf;
}

std::string File::getHeaderBuf() const {
	std::string buf;
	for (const auto& line : lines) {
		buf += line->getHeaderBuf();
	}
	return buf;
}

void File::closeScopes(int newIndent) {
	while (newIndent < indent) {
		--indent;
		std::string closingBrace;
		for (int i = 0; i < indent; ++i) {
			closingBrace += '\t';
		}
		closingBrace += '}';
		lines.push_back(std::make_shared<Line>(closingBrace, false));
	}
}