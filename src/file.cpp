#include "file.hpp"

#include "line.hpp"

#include <fstream>

File::File(const std::string& filename) : indent(0) {
	std::ifstream fin(filename.c_str());
	while (true) {
		std::string buf;
		std::getline(fin, buf);
		if (!fin) {
			break;
		}
		auto line = std::make_shared<Line>(buf);
		while (line->getIndent() > indent) {
			++indent;
		}
		closeScopes(line->getIndent());
		lines.push_back(line);
	}
	closeScopes(0);
}

std::string File::getNewBuf() const {
	std::string buf;
	for (const auto& line : lines) {
		buf += line->getNewBuf();
		buf += '\n';
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
		lines.push_back(std::make_shared<Line>(closingBrace));
	}
}