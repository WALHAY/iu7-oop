#pragma once

#include <cstddef>

class BaseMatrix
{
  public:
    virtual ~BaseMatrix() = 0;

    bool isEmpty() const;

    size_t getRows() const {
		return rows;
	};

    size_t getColumns() const {
		return columns;
	};

  protected:
    size_t rows;
    size_t columns;
};
