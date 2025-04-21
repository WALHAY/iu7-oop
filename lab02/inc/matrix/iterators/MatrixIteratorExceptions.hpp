#pragma once

#include "base/BaseException.hpp"

class IteratorExpiredException : public BaseException
{
    IteratorExpiredException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Iterator pointer expired!")
    {
    }
};

class IteratorInvalidIndexException : public BaseException
{
    IteratorInvalidIndexException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Trying to dereference wrong index!")
    {
    }
};
