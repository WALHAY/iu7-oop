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

    allocateMemory(getSize());
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
Matrix<T>::Matrix(Matrix<U> &&matrix) : Matrix(matrix.getRows(), matrix.getColumns())
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
    allocateMemory(getSize());
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{
    this->rows = matrix.rows;
    this->columns = matrix.columns;
    allocateMemory(getSize());
    std::ranges::copy(matrix.begin(), matrix.end(), begin());
    return *this;
}

template <Storable T>
template <ConvertibleTo<T> U>
Matrix<T> &Matrix<T>::operator=(Matrix<U> &&matrix)
{
    this->rows = matrix.getRows();
    this->columns = matrix.getColumns();
    allocateMemory(getSize());
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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __LINE__);

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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __LINE__);

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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __LINE__);

    Matrix<decltype(std::declval<T>() - std::declval<U>())> result(rows, columns);

    std::ranges::transform(begin(), end(), matrix.begin(), matrix.end(), result.begin(),
                           [](const auto &t, const auto &u) { return t - u; });
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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __LINE__);

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

#pragma region multiplication

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::mul(const U &value) const
{
    Matrix<decltype(std::declval<T>() * std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element * value; });

    return result;
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::mul(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __LINE__);

    Matrix<decltype(std::declval<T>() * std::declval<U>() + std::declval<T>() * std::declval<U>())> newMatrix =
        zero(rows, matrix.getColumns());

    for (auto r = 0; r < rows; r++)
        for (auto c = 0; c < matrix.getColumns(); c++)
            for (auto k = 0; k < columns; k++)
                newMatrix[r][c] += at(r, k) * matrix[k][c];

    return newMatrix;
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::mulAssign(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element * value; });

    return *this;
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::mulAssign(const Matrix<U> &matrix)
{
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __LINE__);

    Matrix<decltype(std::declval<T>() * std::declval<U>() + std::declval<T>() * std::declval<U>())> newMatrix =
        zero(rows, matrix.getColumns());

    for (auto r = 0; r < rows; r++)
    {
        for (auto c = 0; c < matrix.getColumns(); c++)
        {
            value_type value{0};
            for (auto k = 0; k < columns; k++)
            {
                value += at(r, k) * matrix[k][c];
            }
            at(r, c) = value;
        }
    }

    return *this;
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::operator*(const U &value) const
{
    return mul(value);
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::operator*(const Matrix<U> &matrix) const
{
    return mul(matrix);
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::operator*=(const U &value)
{
    return mulAssign(value);
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::operator*=(const Matrix<U> &matrix)
{
    return mulAssign(matrix);
}

#pragma endregion

#pragma region division

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::div(const U &value) const
{
    Matrix<decltype(std::declval<T>() / std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element / value; });

    return result;
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::div(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __LINE__);

    if (det() == value_type{0})
        throw std::exception();

	 return *this * matrix.invert();
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::divAssign(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element / value; });

    return *this;
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::divAssign(const Matrix<U> &matrix)
{
    return *this = *this / matrix;
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::operator/(const U &value) const
{
    return div(value);
}

template <Storable T>
template <MultipliableTo<T> U>
decltype(auto) Matrix<T>::operator/(const Matrix<U> &matrix) const
{
    return div(matrix);
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const U &value)
{
    return divAssign(value);
}

template <Storable T>
template <MultipliableAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const Matrix<U> &matrix)
{
    return divAssign(matrix);
}

#pragma endregion

#pragma region other

template <Storable T>
auto Matrix<T>::det() const
    requires DeterminantComputable<T>
{
    validateSquareSize(__LINE__);

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
    Matrix<T> identityMatrix = Matrix<T>::zero(size, size);

    std::ranges::for_each(std::views::iota(size_t{0}, size),
                          [&](auto index) { identityMatrix(index, index) = value_type{1}; });

    return identityMatrix;
}

template <Storable T>
Matrix<T> Matrix<T>::zero(size_t rows, size_t columns)
    requires HasZeroElement<T>
{
    Matrix<T> zeroMatrix(rows, columns);
    std::ranges::fill(zeroMatrix, value_type{0});

    return zeroMatrix;
}

template <Storable T>
bool Matrix<T>::invertible() const
{
    return isSquare() && det() != value_type{0};
}

template <Storable T>
decltype(auto) Matrix<T>::operator~() const
    requires InvertComputable<T> && std::is_arithmetic_v<T>
{
    return invert();
}

template <Storable T>
decltype(auto) Matrix<T>::operator~() const
    requires InvertComputable<T>
{
    return invert();
}

template <Storable T>
decltype(auto) Matrix<T>::invert() const
    requires InvertComputable<T> && std::is_arithmetic_v<T>
{
    if (!invertible())
        throw NotInvertible(__FILE_NAME__, __FUNCTION__, __LINE__);

    auto [L, U] = this->LU();

    size_t n = rows;
    Matrix<double> invA(n, n);
    Matrix<double> Y(n, n);

    for (auto c = 0; c < n; c++)
        for (auto r = 0; r < n; r++)
        {
            double sum = r == c ? 1 : 0;
            for (int k = 0; k < r; k++)
                sum -= L[r][k] * Y[k][c];
            Y[r][c] = sum;
        }

    for (auto c = 0; c < n; c++)
        for (int r = n - 1; r >= 0; r--)
        {
            double sum = Y[r][c];
            for (int k = r + 1; k < n; ++k)
                sum -= U[r][k] * invA[k][c];
            invA[r][c] = sum / U[r][r];
        }

    return invA;
}

template <Storable T>
decltype(auto) Matrix<T>::invert() const
    requires InvertComputable<T>
{
    if (!invertible())
        throw NotInvertible(__FILE_NAME__, __FUNCTION__, __LINE__);

    auto [L, U] = this->LU();

    size_t n = rows;
    Matrix inverted(n, n);
    Matrix Y(n, n);

    for (auto c = 0; c < n; c++)
    {
        for (auto r = 0; r < n; r++)
        {
            value_type sum = r == c ? value_type{1} : value_type{0};
            for (int k = 0; k < r; k++)
                sum -= L[r][k] * Y[k][c];
            Y[r][c] = sum;
        }
    }

    for (auto c = 0; c < n; c++)
    {
        for (int r = n - 1; r >= 0; r--)
        {
            value_type sum = Y[r][c];
            for (int k = r + 1; k < n; ++k)
                sum -= U[r][k] * inverted[k][c];
            inverted[r][c] = sum / U[r][r];
        }
    }

    return inverted;
}

template <Storable T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> transposed(columns, rows);

    auto newData = std::ranges::transform(std::views::iota(size_t{0}, getSize()), transposed.begin(), [&](auto index) {
        size_t i = index / rows;
        size_t j = index % rows;
        return this->data[j * columns + i];
    });

    return transposed;
}

template <Storable T>
std::pair<Matrix<double>, Matrix<double>> Matrix<T>::LU() const
    requires LUComputable<T> && std::is_arithmetic_v<T>
{
    validateSquareSize(__LINE__);

    auto U = Matrix<double>(*this);
    auto L = Matrix<double>::zero(rows, columns);

    size_t n = rows;
    for (auto r = 0; r < n; r++)
        for (int c = r; c < n; c++)
            L[c][r] = U[c][r] / U[r][r];

    for (auto k = 1; k < n; k++)
    {
        for (int c = k - 1; c < n; c++)
            for (int r = c; r < n; r++)
                L[r][c] = U[r][c] / U[c][c];

        for (int r = k; r < n; r++)
            for (int c = k - 1; c < n; c++)
                U[r][c] = U[r][c] - L[r][k - 1] * U[k - 1][c];
    }

    return std::make_pair(L, U);
}

template <Storable T>
std::pair<Matrix<T>, Matrix<T>> Matrix<T>::LU() const
    requires LUComputable<T>
{
    validateSquareSize(__LINE__);

    auto U = Matrix(*this);
    auto L = Matrix::zero(rows, columns);

    size_t n = rows;
    for (int r = 0; r < n; r++)
        for (int c = r; c < n; c++)
            L[c][r] = U[c][r] / U[r][r];

    for (auto k = 1; k < n; k++)
    {
        for (int c = k - 1; c < n; c++)
            for (int r = c; r < n; r++)
                L[r][c] = U[r][c] / U[c][c];

        for (int r = k; r < n; r++)
            for (int c = k - 1; c < n; c++)
                U[r][c] = U[r][c] - L[r][k - 1] * U[k - 1][c];
    }

    return std::make_pair(L, U);
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
Matrix<T>::Row Matrix<T>::operator[](size_t row)
{
    validateRow(row, __LINE__);

    return Row(*this, row);
}

template <Storable T>
const Matrix<T>::Row Matrix<T>::operator[](size_t row) const
{
    validateRow(row, __LINE__);

    return Row(*this, row);
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
    validateRow(row, __LINE__);
    validateColumn(column, __LINE__);

    return data[row * columns + column];
}

#pragma endregion

#pragma region compare

template <Storable T>
bool Matrix<T>::isZero() const
    requires HasZeroElement<T>
{
    return std::ranges::all_of(begin(), end(), [](const auto &value) { return value == value_type{0}; });
}

template <Storable T>
bool Matrix<T>::isZero() const
    requires HasZeroElement<T> && std::is_floating_point_v<T>
{
    return std::ranges::all_of(begin(), end(),
                               [](const auto &value) { return std::abs(value) < std::numeric_limits<T>::epsilon(); });
}

template <Storable T>
bool Matrix<T>::isIdentity() const
    requires HasIdentityElement<T>
{
    if (rows != columns)
        return false;

    size_t n = getRows();
    return std::ranges::all_of(std::views::iota(size_t{0}, getSize()), [&](size_t index) {
        return this->data[index] == ((index % n == index / n) ? value_type{1} : value_type{0});
    });
}

template <Storable T>
bool Matrix<T>::isIdentity() const
    requires HasIdentityElement<T> && std::is_floating_point_v<T>
{
    if (rows != columns)
        return false;

    size_t n = getRows();
    return std::ranges::all_of(std::views::iota(size_t{0}, getSize()), [&](size_t index) {
        return std::abs(this->data[index] - ((index % n == index / n) ? value_type{1} : value_type{0})) <
               std::numeric_limits<T>::epsilon();
    });
}

template <Storable T>
bool Matrix<T>::equals(Matrix<T> &matrix) const
{
    if (!equalsShape(matrix))
        return false;

    return std::ranges::equal(*this, matrix);
}

template <Storable T>
bool Matrix<T>::operator==(Matrix<T> &matrix) const
{
    return equals(matrix);
}

#pragma endregion

template <Storable T>
void Matrix<T>::validateOtherMatrixSize(size_t rows, size_t columns, int line) const
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
void Matrix<T>::validateSquareSize(int line) const
{
    if (!isSquare())
        throw NotSquareMatrix(__FILE_NAME__, __FUNCTION__, line);
}

template <Storable T>
void Matrix<T>::allocateMemory(size_t elements)
{
    this->data = std::make_shared<T[]>(elements);
}
