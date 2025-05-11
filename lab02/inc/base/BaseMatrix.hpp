#pragma once

#include <cstddef>

class BaseMatrix
{
  public:
    using size_type = std::size_t;

    virtual ~BaseMatrix() = 0;

    bool isEmpty() const;

    size_type getSize() const
    {
        return rows * columns;
    }

    size_t getRows() const
    {
        return rows;
    }

    size_t getColumns() const
    {
        return columns;
    }

  protected:
    size_t rows;
    size_t columns;
};
