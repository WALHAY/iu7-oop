#pragma once

#include "collection/BaseException.hpp"
#include <string>

class OutOfRangeException : public BaseException
{
  public:
    OutOfRangeException(const std::string &filename, const std::string &classname, const std::string &method, int line)
        : BaseException(filename, classname, method, line, "Invalid key access")
    {
    }
};

class InvalidIterator : public BaseException
{
  public:
    InvalidIterator(const std::string &filename, const std::string &classname, const std::string &method, int line)
        : BaseException(filename, classname, method, line, "Invalid iterator")
    {
    }
};
