#include "base/BaseMatrix.hpp"
#include <cstddef>

BaseMatrix::BaseMatrix() noexcept : rows(0), columns(0)
{
}

BaseMatrix::BaseMatrix(const size_t rows, const size_t columns) noexcept : rows(rows), columns(columns)
{
}

size_t BaseMatrix::getRows() const
{
    return rows;
}

size_t BaseMatrix::getColumns() const
{
    return rows;
}

bool BaseMatrix::isEmpty() const {
	return rows == 0 || columns == 0;
}
