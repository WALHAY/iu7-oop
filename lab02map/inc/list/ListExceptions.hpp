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

class NodeAllocationException : public BaseException
{
  public:
    NodeAllocationException(const std::string &filename, const std::string &classname, const std::string &method,
                                int line)
        : BaseException(filename, classname, method, line, "Failed to allocate memory for list node")
    {
    }
};

class EmptyListException : public BaseException
{
  public:
    EmptyListException(const std::string &filename, const std::string &classname, const std::string &method,
                                int line)
        : BaseException(filename, classname, method, line, "Trying to get value in empty list")
    {
    }
};
