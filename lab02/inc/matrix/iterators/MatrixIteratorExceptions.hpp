#pragma once

#include "base/BaseException.hpp"

class IteratorExpiredException : public BaseException
{
  public:
    IteratorExpiredException(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Iterator pointer expired!")
    {
    }
};

class IteratorInvalidIndexException : public BaseException
{
  public:
    IteratorInvalidIndexException(const char *filename, const char *method, int line, time_t time)
        : BaseException(filename, method, line, time, "Trying to dereference wrong index!")
    {
    }
};
