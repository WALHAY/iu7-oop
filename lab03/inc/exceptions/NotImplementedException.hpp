#pragma once

#include "exceptions/BaseException.hpp"

class NotImplementedException : public BaseException {
public:
	NotImplementedException(const char *filename, const char *method, int line) : BaseException(filename, method, line)
	{
	}
};

