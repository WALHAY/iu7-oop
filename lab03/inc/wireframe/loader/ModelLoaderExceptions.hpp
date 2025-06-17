#pragma once

#include <exceptions/BaseException.hpp>

class ModelValidationFailedException : public BaseException
{
  public:
    ModelValidationFailedException(const char *filename, const char *method, int line)
        : BaseException(filename, method, line)
    {
    }
};
