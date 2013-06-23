#pragma once

#include <string>

class Tokenizer {
public:
	Tokenizer(const std::string& buf);

	/// returns an empty string when the end of the line has been reached
	std::string getNextToken();

	size_t getPos() const;
	void setPos(size_t);
private:
	char charAt(size_t p);

	const std::string& buf;
	size_t pos = 0;
};