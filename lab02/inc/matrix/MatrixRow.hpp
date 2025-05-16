#pragma once

#include <matrix/Matrix.hpp>
#include <matrix/MatrixExceptions.hpp>

template <Storable T>
Matrix<T>::Row::Row(const Matrix<T> &matrix, size_t row) noexcept : matrix(matrix), row(row)
{
}

template <Storable T>
T &Matrix<T>::Row::operator[](size_t index)
{
    if (index < 0 || index >= matrix.columns)
        throw MatrixColumnOutOfBounds(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    return matrix.data[row * matrix.columns + index];
}

template <Storable T>
const T &Matrix<T>::Row::operator[](size_t index) const
{
    if (index < 0 || index >= matrix.columns)
        throw MatrixColumnOutOfBounds(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    return matrix.data[row * matrix.columns + index];
}
