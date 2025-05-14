#pragma once

#include <memory>

class BaseMatrixIterator
{
  public:
    using size_type = size_t;

    virtual ~BaseMatrixIterator() = 0;

  protected:
	size_type currentIndex = 0;
	size_type matrixSize = 0;
};
