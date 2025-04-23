#pragma once

#include "base/BaseException.hpp"
class InvalidAddSubSizeExcepetion : public BaseException
{
  public:
    InvalidAddSubSizeExcepetion(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid addition/subtraction matrix size")
    {
    }
};
