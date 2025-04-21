#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <ranges>

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
}

template <typename T>
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

template<typename T>
auto Matrix<T>::begin() -> iterator {
	return iterator(*this);
}

template<typename T>
auto Matrix<T>::end() -> iterator {
	return iterator(*this, rows * columns);
}

#pragma region addition
template <typename T>
template <typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const U &value) const
{
}

template <typename T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const U &value)
{
}

template <typename T>
template <typename U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const Matrix<U> &matrix) const
{
}

template <typename T>
template <typename U>
Matrix<decltype(T() + U())> &Matrix<T>::operator+=(const Matrix<U> &matrix)
{
}
#pragma endregion
