#include "../inc/Matrix.hpp"
#include <exception>
#include <initializer_list>
#include <vector>
#include <ranges>

template <typename T> Matrix<T>::Matrix() noexcept
{
    this->rows = 0;
    this->columns = 0;
}

template <typename T> Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> matrix)
{
    size_t rows = matrix.size();

    // std::ranges::for_each(matrix, [this](std::initializer_list<T> list) { this->data.push_back(std::vector<T>(list.begin(), list.end())); });
}

template <typename T> void Matrix<T>::resize(size_t rows, size_t columns)
{
    // std::ranges::for_each(this->data, [&columns](std::vector<T> &v) { v.resize(columns, T()); });
    this->data.resize(rows, std::vector<T>(columns, T()));
}

template <typename T> T& Matrix<T>::at(const size_t row, const size_t column)
{
}

template<typename T>
Matrix<T> Matrix<T>::add(const T &value) const
{
}

template<typename T>
void Matrix<T>::validateRow(const size_t row) const {
	if(row < 0 || row > rows)
		throw InvalidRowException("Invalid row");
}

template<typename T>
void Matrix<T>::validateColumn(const size_t column) const {
	if(column < 0 || column > columns)
		throw InvalidColumnException("Invalid column");
}
