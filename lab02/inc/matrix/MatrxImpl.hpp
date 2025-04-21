#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
}

template <Storable T>
Matrix<T>::Matrix(const Matrix<T> &matrix)
{
    this->rows = matrix.rows;
    this->columns = matrix.columns;

    this->data = std::make_shared<T[]>(rows * columns);

	size_t index = 0;
	for(auto it = matrix.begin(); it != matrix.end(); ++it)
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

#pragma region addition
template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const U &value) const
{
    Matrix<decltype(T() + U())> newMatrix(*this);
    std::ranges::transform(newMatrix, newMatrix.begin(), [&value](const value_type &element) { return element + value; });
	
    return newMatrix;
}

template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const U &value)
{
}

template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const Matrix<U> &matrix) const
{
}

template <Storable T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const Matrix<U> &matrix)
{
}
#pragma endregion
