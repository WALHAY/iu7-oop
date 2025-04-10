#pragma once

#include <cstddef>

class BaseMatrix {
public:
	BaseMatrix();
	BaseMatrix(const size_t rows, const size_t columns);

	virtual ~BaseMatrix() = 0;

	bool isEmpty() const;
	size_t getRows() const;
	size_t getColumns() const;
protected:
	size_t rows;
	size_t columns;
};
