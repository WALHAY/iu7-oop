#pragma once

#include "collection/BaseException.hpp"
#include <string>

class OutOfRangeException : public BaseException {
	public:
		OutOfRangeException(std::string filename, std::string classname, std::string method, int line);
};

class InvalidIterator : public BaseException {
	public:
		InvalidIterator(std::string filename, std::string classname, std::string method, int line);
};
