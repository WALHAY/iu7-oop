#pragma once

#include "collection/BaseException.hpp"
#include <string>

class InvalidKeyException : public BaseException
{
  public:
    InvalidKeyException(const char *filename, const char *classname, const char *method, int line)
        : BaseException(filename, classname, method, line, "Invalid key access")
    {
    }
};

class InvalidIterator : public BaseException
{
  public:
    InvalidIterator(const char *filename, const char *classname, const char *method, int line)
        : BaseException(filename, classname, method, line, "Invalid iterator")
    {
    }
};
