#pragma once

#include <cstddef>

class BaseMatrixIterator
{
  public:
    using size_type = std::size_t;

    virtual ~BaseMatrixIterator() = 0;

  protected:
    size_type currentIndex = 0;
    size_type matrixSize = 0;
};
