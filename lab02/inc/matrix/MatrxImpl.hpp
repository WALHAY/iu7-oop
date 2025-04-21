#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), columns(columns)
{
    this->data = std::make_shared<T[]>(rows * columns);
}

template <Storable T>
Matrix<T>::Matrix(const Matrix<T> &matrix) : Matrix(matrix.rows, matrix.columns)
{

    size_t index = 0;
    for (auto it = matrix.begin(); it != matrix.end(); ++it)
    {
        this->data[index++] = *it;
    }
}

template <Storable T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ilist)
{
    this->rows = ilist.size();
    this->columns = std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); }));

    this->data = std::make_shared<T[]>(rows * columns);

    size_t y = 0;
    for (auto &list : ilist)
    {
        size_t x = 0;
        for (auto &value : list)
        {
            this->data[y * this->columns + x++] = value;
        }
        y++;
    }
}

template <Storable T>
auto Matrix<T>::begin() -> iterator
{
    return iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() -> iterator
{
    return iterator(*this, rows * columns);
}

template <Storable T>
auto Matrix<T>::begin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() const -> const_iterator
{
    return const_iterator(*this, rows * columns);
}

template <Storable T>
auto Matrix<T>::cbegin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::cend() const -> const_iterator
{
    return const_iterator(*this, rows * columns);
}

#pragma region addition
template <Storable T>
template <AddableTo<T> U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const U &value) const
{
    Matrix<decltype(T() + U())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const value_type &element) { return element + value; });

    return result;
}

template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const U &value)
{
}

template <Storable T>
template <AddableTo<T> U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const Matrix<U> &matrix) const
{
    Matrix<decltype(T() + U())> result(matrix.rows, matrix.columns);

    std::ranges::transform(std::ranges::views::iota(size_t(0), rows * columns), result.begin(),
                           [this, &matrix](size_type index) { return this->data[index] + matrix.data[index]; });
	return result;
}

template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const Matrix<U> &matrix)
{
}
#pragma endregion
