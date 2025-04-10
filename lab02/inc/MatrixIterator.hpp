#pragma once

#include "base/BaseMatrixIterator.hpp"
#include "Matrix.hpp"

template <typename T> class MatrixIterator : public BaseMatrixIterator<T>
{
    friend class Matrix<T>;

  public:
    MatrixIterator<T>(const MatrixIterator<T> &iterator) noexcept;
    MatrixIterator<T>(MatrixIterator<T> &&iterator) noexcept;

    MatrixIterator &operator=(const MatrixIterator &) noexcept;
    MatrixIterator &operator=(MatrixIterator &&) noexcept;

    MatrixIterator<T> operator+(const size_t offset) const;
    MatrixIterator<T> &operator+=(const size_t offset);

    MatrixIterator<T> operator++(int);
    MatrixIterator<T> &operator++();
};
