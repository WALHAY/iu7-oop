#include "../inc/BaseMatrix.hpp"
#include <cstddef>

BaseMatrix::BaseMatrix() : rows(0), columns(0) {}

BaseMatrix::BaseMatrix(const size_t rows, const size_t columns) : rows(rows), columns(columns) {}

size_t BaseMatrix::getRows() const{
	return this->rows;
}

size_t BaseMatrix::getColumns() const{
	return this->rows;
}
