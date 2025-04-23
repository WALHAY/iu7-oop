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

class InvalidInitListSizeException : public BaseException
{
  public:
    InvalidInitListSizeException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid initializer list dimension")
    {
    }
};

class InvalidRowException : public BaseException
{
  public:
    InvalidRowException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix row")
    {
    }
};

class InvalidColumnException : public BaseException
{
  public:
    InvalidColumnException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Invalid matrix column")
    {
    }
};

class DeterminantSizeException : public BaseException
{
  public:
    DeterminantSizeException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line, "Matrix is not square")
    {
    }
};
