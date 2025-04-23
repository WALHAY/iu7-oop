#pragma once

#include <matrix/Matrix.hpp>
#include <matrix/MatrixExceptions.hpp>

template <Storable T>
Matrix<T>::RowProxy::RowProxy(std::shared_ptr<T[]> data, size_t row, size_t matrixColumns)
    : dataPtr(data), row(row), matrixColumns(matrixColumns)
{
}

template <Storable T>
T &Matrix<T>::RowProxy::operator[](size_t index)
{
    if (index < 0 || index >= matrixColumns)
        throw InvalidColumnException(__FILE_NAME__, __FUNCTION__, __LINE__);
    return dataPtr.lock()[row * matrixColumns + index];
}

template <Storable T>
const T &Matrix<T>::RowProxy::operator[](size_t index) const
{
    return *this[index];
}
