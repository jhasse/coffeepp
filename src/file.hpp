#pragma once

#include <memory>
#include <string>
#include <vector>

class Line;

class File {
public:
	File(const std::string& filename);
	std::string getNewBuf() const;
private:
	void closeScopes(int newIndent);

	std::vector<std::shared_ptr<Line>> lines;
	int indent;
};