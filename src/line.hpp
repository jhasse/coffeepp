#pragma once

#include <boost/optional.hpp>
#include <string>
#include <sstream>

class IndentionType;

class Line {
public:
	Line(const std::string& buf, bool waitForEndComment, bool wasBeginScope,
	     boost::optional<IndentionType>& indentionType);
	int getIndent() const;
	std::string getNewBuf() const;
	std::string getHeaderBuf() const;
	bool isEmpty() const;
	bool isBeginScope() const;
	bool isBeginComment() const;
private:
	/// the line as Coffee++
	std::string oldBuf;

	/// C++
	std::stringstream newBuf;

	/// C++ line that should be added to a header file
	std::stringstream headerBuf;

	/// comment at the beginning of the line
	std::string commentAtBeginning;

	/// how much this line is indented
	int indent;

	bool beginScope;

	bool beginComment;
};
