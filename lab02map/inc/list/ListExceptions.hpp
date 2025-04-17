#pragma once

#include <collection/BaseException.hpp>
#include <cstring>

class InvalidIndexAccessException : public BaseException
{
  public:
    InvalidIndexAccessException(const std::string &filename, const std::string &classname, const std::string &method,
                                int line)
        : BaseException(filename, classname, method, line, "List invalid index access")
    {
    }
};
