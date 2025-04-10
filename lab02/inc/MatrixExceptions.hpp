#pragma once

#include "BaseException.hpp"

class InvalidRowException : public BaseException {
public:
	explicit InvalidRowException(const std::string);
};

class InvalidColumnException : public BaseException {
public:
	explicit InvalidColumnException(const std::string message);
};

class MemoryException : public BaseException {
public:
	explicit MemoryException(const std::string message);
};
