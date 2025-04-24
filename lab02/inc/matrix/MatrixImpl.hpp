#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <matrix/MatrixExceptions.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
    this->rows = rows;
    this->columns = columns;

    this->data = std::make_shared<T[]>(getSize());
}

template <Storable T>
Matrix<T>::Matrix(size_t size) : Matrix(size, size)
{
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(const U *value, size_t rows, size_t columns) : Matrix(rows, columns)
{
    std::ranges::copy(value, value + getSize(), begin());
}

template <Storable T>
Matrix<T>::Matrix(const T *value, size_t rows, size_t columns) : Matrix(rows, columns)
{
    std::ranges::copy(value, value + getSize(), begin());
}

template <Storable T>
template <std::ranges::input_range R>
    requires ConvertibleTo<std::ranges::range_value_t<R>, T>
Matrix<T>::Matrix(const R &range, size_t rows, size_t columns) : Matrix(rows, columns)
{
    std::ranges::copy(range, begin());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(const Matrix<U> &matrix) : Matrix(matrix.getRows(), matrix.getColumns())
{
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
Matrix<T>::Matrix(const Matrix<T> &matrix) : Matrix(matrix.getRows(), matrix.getColumns())
{
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<U>> ilist)
    : Matrix(ilist.size(),
             std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); })))

{
    if (std::ranges::any_of(ilist, [this](const auto &l) { return l.size() != this->columns; }))
        throw InitListWrongSize(__FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::copy(ilist | std::views::join, begin());
}

template <Storable T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ilist)
    : Matrix(ilist.size(),
             std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); })))

{
    if (std::ranges::any_of(ilist, [this](const auto &l) { return l.size() != this->columns; }))
        throw InitListWrongSize(__FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::copy(ilist | std::views::join, begin());
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T> &Matrix<T>::operator=(const Matrix<U> &matrix)
{
    this->rows = matrix.getRows();
    this->columns = matrix.getColumns();
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{
    this->rows = matrix.rows;
    this->columns = matrix.columns;
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
    return *this;
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T> &Matrix<T>::operator=(Matrix<U> &&matrix)
{
    this->rows = matrix.getRows();
    this->columns = matrix.getColumns();
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
    return *this;
}

template <Storable T>
auto Matrix<T>::begin() -> iterator
{
    return iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() -> iterator
{
    return iterator(*this) + getSize();
}

template <Storable T>
auto Matrix<T>::begin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::end() const -> const_iterator
{
    return const_iterator(*this) + getSize();
}

template <Storable T>
auto Matrix<T>::cbegin() const -> const_iterator
{
    return const_iterator(*this);
}

template <Storable T>
auto Matrix<T>::cend() const -> const_iterator
{
    return const_iterator(*this) + getSize();
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
decltype(auto) Matrix<T>::add(const Matrix<U> &matrix) const
{
    validateEqualSize(matrix.getRows(), matrix.getColumns(), __LINE__);

    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(rows, columns);

    std::ranges::transform(*this, matrix, result.begin(), [](const auto &t, const auto &u) { return t + u; });
    return result;
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::addAssign(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element + value; });

    return *this;
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::addAssign(const Matrix<U> &matrix)
{
    validateEqualSize(matrix.getRows(), matrix.getColumns(), __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t + u; });

    return *this;
}

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::operator+(const U &value) const
{
    return add(value);
}

template <Storable T>
template <AddableTo<T> U>
decltype(auto) Matrix<T>::operator+(const Matrix<U> &matrix) const
{
    return add(matrix);
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::operator+=(const U &value)
{
    return addAssign(value);
}

template <Storable T>
template <AddableAssignable<T> U>
Matrix<T> &Matrix<T>::operator+=(const Matrix<U> &matrix)
{
    return addAssign(matrix);
}

#pragma endregion

#pragma region subtraction

template <Storable T>
template <SubtractableTo<T> U>
decltype(auto) Matrix<T>::sub(const U &value) const
{
    Matrix<decltype(std::declval<T>() - std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element - value; });

    return result;
}

template <Storable T>
template <SubtractableTo<T> U>
decltype(auto) Matrix<T>::sub(const Matrix<U> &matrix) const 
{
    validateEqualSize(matrix.getRows(), matrix.getColumns(), __LINE__);

    Matrix<decltype(std::declval<T>() - std::declval<U>())> result(rows, columns);

    std::ranges::transform(begin(), end(), matrix.begin(), matrix.end(), result.begin(), [](const auto &t, const auto &u) { return t - u; });
    return result;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::subAssign(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element - value; });

    return *this;
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::subAssign(const Matrix<U> &matrix)
{
    validateEqualSize(matrix.getRows(), matrix.getColumns(), __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t - u; });

    return *this;
}

template <Storable T>
template <SubtractableTo<T> U>
decltype(auto) Matrix<T>::operator-(const U &value) const
{
    return sub(value);
}

template <Storable T>
template <SubtractableTo<T> U>
decltype(auto) Matrix<T>::operator-(const Matrix<U> &matrix) const
{
    return sub(matrix);
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::operator-=(const U &value)
{
    return subAssign(value);
}

template <Storable T>
template <SubtractableAssignable<T> U>
Matrix<T> &Matrix<T>::operator-=(const Matrix<U> &matrix)
{
    return subAssign(matrix);
}

#pragma endregion

#pragma region other

template <Storable T>
auto Matrix<T>::det() const
    requires DeterminantComputable<T>
{
    validateDeterminantSize(__LINE__);

    Matrix<T> temp(*this);
    size_t n = rows;

    std::ranges::for_each(std::views::iota(size_t{0}, n - 1), [&temp, n](auto k) {
        std::ranges::for_each(std::views::iota(size_t{k + 1}, n), [&temp, n, k](auto i) {
            std::ranges::for_each(std::views::iota(size_t{k + 1}, n), [&temp, i, k](auto j) {
                temp(i, j) = (temp(k, k) * temp(i, j) - temp(i, k) * temp(k, j));
                if (k > 0)
                    temp(i, j) /= temp(k - 1, k - 1);
            });
        });
    });

    return temp(rows - 1, columns - 1);
}

template <Storable T>
Matrix<T> Matrix<T>::identity(size_t size)
    requires HasIdentityElement<T> && HasZeroElement<T>
{
    Matrix<T> identityMatrix(size);
    std::ranges::transform(std::views::iota(size_t{0}, identityMatrix.getSize()), identityMatrix.begin(),
                           [&, size](auto index) { return (index % size == index / size) ? T{1} : T{0}; });

    return identityMatrix;
}

template <Storable T>
Matrix<T> Matrix<T>::zero(size_t rows, size_t columns)
    requires HasZeroElement<T>
{
    Matrix<T> zeroMatrix(rows, columns);
    std::ranges::fill(zeroMatrix, T{0});

    return zeroMatrix;
}

template <Storable T>
Matrix<T> &Matrix<T>::transposed()
{
    return *this = transpose();
}

template <Storable T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> transposed(columns, rows);

    std::ranges::transform(std::views::iota(size_t{0}, getSize()), transposed.begin(), [&, transposed](auto index) {
        size_t i = index / rows;
        size_t j = index % rows;
        return this->data[j * columns + i];
    });

    return transposed;
}

template <Storable T>
void Matrix<T>::swapRows(size_t first, size_t second)
{
    validateRow(first, __LINE__);
    validateRow(second, __LINE__);

    if (first == second)
        return;

    std::ranges::swap_ranges(begin() + first * columns, begin() + first * columns + columns, begin() + second * columns,
                             begin() + second * columns + columns);
}

template <Storable T>
void Matrix<T>::swapColumns(size_t first, size_t second)
{
    validateColumn(first, __LINE__);
    validateColumn(second, __LINE__);

    if (first == second)
        return;

    auto column_view = [&](size_t column) {
        return std::views::iota(size_t{0}, rows) |
               std::views::transform([&](size_t row) { return data[row * columns + column]; });
    };

    auto colFirst = column_view(first);
    auto colSecond = column_view(second);

    std::ranges::swap_ranges(colFirst, colSecond);
}

#pragma endregion

#pragma region lookup

template <Storable T>

Matrix<T>::RowProxy Matrix<T>::operator[](size_t row)
{
    validateRow(row, __LINE__);

    return RowProxy(*this, row);
}

template <Storable T>
const Matrix<T>::RowProxy Matrix<T>::operator[](size_t row) const
{
    return operator[](row);
}

template <Storable T>
auto Matrix<T>::operator()(size_t row, size_t column) -> reference
{
    return at(row, column);
}

template <Storable T>
auto Matrix<T>::operator()(size_t row, size_t column) const -> const_reference
{
    return at(row, column);
}

template <Storable T>
auto Matrix<T>::at(size_t row, size_t column) -> reference
{
    validateRow(row, __LINE__);
    validateColumn(column, __LINE__);

    return data[row * columns + column];
}

template <Storable T>
auto Matrix<T>::at(size_t row, size_t column) const -> const_reference
{
    return at(row, column);
}

#pragma endregion

template <Storable T>
void Matrix<T>::validateEqualSize(size_t rows, size_t columns, int line) const
{
    if (rows != this->rows || columns != this->columns)
        throw NotEqualSize(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateRow(size_t row, int line) const
{
    if (row < 0 || row >= rows)
        throw MatrixRowOutOfBounds(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateColumn(size_t column, int line) const
{
    if (column < 0 || column >= columns)
        throw MatrixColumnOutOfBounds(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::validateDeterminantSize(int line) const
{
    if (columns != rows)
        throw NotSquareMatrix(__FILE_NAME__, __FUNCTION__, line);
}
