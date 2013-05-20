#pragma once

#include <string>
#include <sstream>

class Line {
public:
	Line(const std::string& buf, bool waitForEndComment);
	int getIndent() const;
	std::string getNewBuf() const;
	bool isEmpty() const;
	bool isBeginScope() const;
	bool isBeginComment() const;
private:
	/// the line as Coffee++
	std::string oldBuf;

	/// C++
	std::stringstream newBuf;

	/// comment at the beginning of the line
	std::string comment;

	/// how much this line is indented
	int indent;

	bool beginScope;

	bool beginComment;
};