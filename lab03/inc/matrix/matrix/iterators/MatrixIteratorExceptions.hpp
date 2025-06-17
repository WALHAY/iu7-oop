#pragma once

#include "exceptions/BaseException.hpp"
#include <ctime>

class IteratorExpiredException : public BaseException
{
  public:
    IteratorExpiredException(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};

class IteratorInvalidIndexException : public BaseException
{
  public:
    IteratorInvalidIndexException(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line)
    {
    }
};
