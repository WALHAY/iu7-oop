#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_type size)
{
    this->size = size;
    this->data = std::make_shared<T[]>(getElements());
}

template <Storable T>
Matrix<T>::Matrix(const Matrix<T> &matrix) : Matrix(matrix.size)
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
    this->size = std::make_pair(
        ilist.size(), std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); })));

    this->data = std::make_shared<T[]>(getElements());

    size_t y = 0;
    for (auto &list : ilist)
    {
        size_t x = 0;
        for (auto &value : list)
        {
            this->data[y * this->size.second + x++] = value;
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
Matrix<decltype(T() + U())> Matrix<T>::add(const U &value) const
{
    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element + value; });

    return result;
}

template <Storable T>
template <AddableTo<T> U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const U &value) const
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
Matrix<decltype(T() + U())> Matrix<T>::add(const Matrix<U> &matrix) const
{
    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(getSize());

    std::ranges::transform(*this, matrix, result.begin(), [](const auto &t, const auto &u) { return t + u; });
    return result;
}

template <Storable T>
template <AddableTo<T> U>
Matrix<decltype(T() + U())> Matrix<T>::operator+(const Matrix<U> &matrix) const
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
