#pragma once

#include "exceptions/BaseException.hpp"

class NotAFileException : public BaseException
{
  public:
    NotAFileException(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class FileOpenException : public BaseException
{
  public:
    FileOpenException(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};

class FileNotExistException : public BaseException
{
  public:
    FileNotExistException(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};
