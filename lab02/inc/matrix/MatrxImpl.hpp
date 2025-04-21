#pragma once

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
    // this->columns = std::ranges::max_element(ilist, std::ranges::less{}, [](const auto &list) { return list.size(); });

    this->data = std::make_shared<T>(rows * columns);
}
