#pragma once

#include "exceptions/BaseException.hpp"

class SceneManagerNotSetException : public BaseException
{
  public:
    SceneManagerNotSetException(const char *filename, const char *funcName, int line)
        : BaseException(filename, funcName, line)
    {
    }
};

class SelectionManagerNotSetException : public BaseException
{
  public:
    SelectionManagerNotSetException(const char *filename, const char *funcName, int line)
        : BaseException(filename, funcName, line)
    {
    }
};

class NoCameraSetException : public BaseException
{
  public:
    NoCameraSetException(const char *filename, const char *method, int line) : BaseException(filename, method, line)
    {
    }
};
