#pragma once

#include <cstddef>
#include <utility>

class BaseMatrix
{
  public:
	using size_type = std::size_t;

    virtual ~BaseMatrix() = 0;

    bool isEmpty() const;

    size_type getRows() const {
		return rows;
	};

    size_type getColumns() const {
		return columns;
	};

	std::pair<size_type, size_type> getShape() {
		return std::make_pair(rows, columns);
	}

  protected:
    size_type rows;
    size_type columns;
};
