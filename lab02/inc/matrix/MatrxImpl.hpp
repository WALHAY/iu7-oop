#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <matrix/MatrixExceptions.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_type size)
{
    this->size = size;
    this->data = std::make_shared<T[]>(getElements());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(const Matrix<U> &matrix) : Matrix(matrix.getSize())
{
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
Matrix<T>::Matrix(const Matrix<T> &matrix) : Matrix(matrix.getSize())
{
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ilist)
    : Matrix(std::make_pair(
          ilist.size(), std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); }))))

{
    if (std::ranges::any_of(ilist, [this](const auto &l) { return l.size() != this->size.second; }))
        throw InvalidInitListSizeException(__FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::copy(ilist | std::views::join, begin());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T> &Matrix<T>::operator=(const Matrix<U> &matrix)
{
    this->size = matrix.getSize();
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{
    this->size = matrix.getSize();
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T> &Matrix<T>::operator=(Matrix<U> &&matrix)
{
    this->size = matrix.getSize();
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
auto Matrix<T>::begin() -> iterator
{
    return iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() -> iterator
{
    return iterator(*this, getElements());
}

template <Storable T>
auto Matrix<T>::begin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() const -> const_iterator
{
    return const_iterator(*this, getElements());
}

template <Storable T>
auto Matrix<T>::cbegin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::cend() const -> const_iterator
{
    return const_iterator(*this, getElements());
}

#pragma region addition

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::add(const U &value) const
{
    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element + value; });

    return result;
}

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::operator+(const U &value) const
{
    return add(value);
}

template <Storable T>
template <AddableConvertible<T> U>
Matrix<T> &Matrix<T>::operator+=(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element + value; });

    return *this;
}

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::add(const Matrix<U> &matrix) const
{
    validateAddSubSize(matrix.getSize(), __LINE__);
    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(getSize());

    std::ranges::transform(*this, matrix, result.begin(), [](const auto &t, const auto &u) { return t + u; });
    return result;
}

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::operator+(const Matrix<U> &matrix) const
{
    return add(matrix);
}

template <Storable T>
template <AddableConvertible<T> U>
Matrix<T> &Matrix<T>::operator+=(const Matrix<U> &matrix)
{
    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t + u; });

    return *this;
}
#pragma endregion

#pragma region lookup

template <Storable T>

Matrix<T>::RowProxy Matrix<T>::operator[](size_t row)
{
    validateRow(row, __LINE__);
    return RowProxy(data, row, size.second);
}

template <Storable T>
const Matrix<T>::RowProxy Matrix<T>::operator[](size_t row) const
{
    validateRow(row, __LINE__);
    return operator[](row);
}

#pragma endregion

#pragma region other

template <Storable T>
auto Matrix<T>::det() const
{
    validateDeterminantSize(__LINE__);

    if (getSize().first == 1)
        return (double)data[0];

    double value = 0;
    for (size_t i = 0; i < getSize().first; ++i)
    {
        Matrix<T> temp = matrixExclude(0, i);
        double minor = data[0] * temp.det();

        if (i % 2 == 0)
            value += minor;
        else
            value -= minor;
    }
    return value;
}

// static Matrix<T> identity();
// static Matrix<T> zero();
//
// Matrix<T> transpose() const;
// Matrix<T> invert() const;
#pragma endregion

template <Storable T>
void Matrix<T>::validateAddSubSize(size_type size, int line) const
{
    if (size.first != this->size.first || size.second != this->size.second)
        throw InvalidAddSubSizeExcepetion(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateRow(size_t row, int line) const
{
    if (row < 0 || row >= size.first)
        throw InvalidRowException(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateColumn(size_t column, int line) const
{
    if (column < 0 || column >= size.second)
        throw InvalidColumnException(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateDeterminantSize(int line) const
{
    if (getSize().first != getSize().second)
        throw DeterminantSizeException(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
Matrix<T> Matrix<T>::matrixExclude(size_t row, size_t column) const
{
    Matrix<T> result(std::make_pair(getSize().first - 1, getSize().second - 1));

    auto indices = std::views::iota(size_t{0}, getElements()) | std::views::filter([&, row, column](auto value) {
                       return value % this->getSize().second != column && value / this->getSize().second != row;
                   });
    std::ranges::transform(indices, result.begin(), [&](size_t index) { return this->data[index]; });
    return result;
}
