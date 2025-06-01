#pragma once

#include <algorithm>
#include <matrix/Matrix.hpp>
#include <matrix/MatrixExceptions.hpp>
#include <ranges>

template <Storable T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
    validateMatrixSize(rows, columns, __FILE_NAME__, __FUNCTION__, __LINE__);

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
Matrix<T>::Matrix(const R range, size_t rows, size_t columns) : Matrix(rows, columns)
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
        throw InitListInvalidSize(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    std::ranges::copy(ilist | std::views::join, begin());
}

template <Storable T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> ilist)
    : Matrix(ilist.size(),
             std::ranges::max(ilist | std::views::transform([](const auto &list) { return list.size(); })))

{
    if (std::ranges::any_of(ilist, [this](const auto &l) { return l.size() != this->columns; }))
        throw InitListInvalidSize(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

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

template <Storable T>
auto Matrix<T>::rbegin() -> reverse_iterator
{
    return reverse_iterator(*this);
}

template <Storable T>
auto Matrix<T>::rend() -> reverse_iterator
{
    return reverse_iterator(*this) + getSize();
}

template <Storable T>
auto Matrix<T>::rbegin() const -> const_reverse_iterator
{
    return const_reverse_iterator(*this);
}

template <Storable T>
auto Matrix<T>::rend() const -> const_reverse_iterator
{
    return const_reverse_iterator(*this) + getSize();
}

template <Storable T>
auto Matrix<T>::crbegin() const -> const_reverse_iterator
{
    return const_reverse_iterator(*this);
}

template <Storable T>
auto Matrix<T>::crend() const -> const_reverse_iterator
{
    return const_reverse_iterator(*this) + getSize();
}

#pragma region addition

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::add(const U &value) const
{
    Matrix<decltype(std::declval<T>() + std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element + value; });

    return result;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::add(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t + u; });

    return *this;
}

template <Storable T>
template <Addable<T> U>
decltype(auto) Matrix<T>::operator+(const U &value) const
{
    return add(value);
}

template <Storable T>
template <Addable<T> U>
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
template <Subtractable<T> U>
decltype(auto) Matrix<T>::sub(const U &value) const
{
    Matrix<decltype(std::declval<T>() - std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element - value; });

    return result;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::sub(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t - u; });

    return *this;
}

template <Storable T>
template <Subtractable<T> U>
decltype(auto) Matrix<T>::operator-(const U &value) const
{
    return sub(value);
}

template <Storable T>
template <Subtractable<T> U>
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
template <Multipliable<T> U>
decltype(auto) Matrix<T>::mul(const U &value) const
{
    Matrix<decltype(std::declval<T>() * std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element * value; });

    return result;
}

template <Storable T>
template <Multipliable<T> U>
decltype(auto) Matrix<T>::mul(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __FILE_NAME__, __FUNCTION__, __LINE__);

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
template <Multipliable<T> U>
decltype(auto) Matrix<T>::operator*(const U &value) const
{
    return mul(value);
}

template <Storable T>
template <Multipliable<T> U>
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
template <Divisible<T> U>
decltype(auto) Matrix<T>::div(const U &value) const
{
    Matrix<decltype(std::declval<T>() / std::declval<U>())> result(*this);
    std::ranges::transform(result, result.begin(), [&value](const auto &element) { return element / value; });

    return result;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::div(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getColumns(), matrix.getRows(), __FILE_NAME__, __FUNCTION__, __LINE__);

    if (det() == value_type{0})
        throw DivisionZeroDeterminant(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    return *this * matrix.invert();
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divAssign(const U &value)
{
    std::ranges::transform(*this, begin(), [&value](const auto &element) { return element / value; });

    return *this;
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::divAssign(const Matrix<U> &matrix)
{
    return *this = *this / matrix;
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::operator/(const U &value) const
{
    return div(value);
}

template <Storable T>
template <Divisible<T> U>
decltype(auto) Matrix<T>::operator/(const Matrix<U> &matrix) const
{
    return div(matrix);
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const U &value)
{
    return divAssign(value);
}

template <Storable T>
template <DivisibleAssignable<T> U>
Matrix<T> &Matrix<T>::operator/=(const Matrix<U> &matrix)
{
    return divAssign(matrix);
}

#pragma endregion

#pragma region hadamard

template <Storable T>
template <MultipliableAssignable<T> U>
decltype(auto) Matrix<T>::hadamardMul(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    Matrix<decltype(std::declval<T>() * std::declval<U>())> result(rows, columns);

    std::ranges::transform(*this, matrix, result.begin(), [](const auto &t, const auto &u) { return t * u; });
    return result;
}

template <Storable T>
template <MultipliableAssignable<T> U>
decltype(auto) Matrix<T>::hadamardDiv(const Matrix<U> &matrix) const
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    Matrix<decltype(std::declval<T>() / std::declval<U>())> result(rows, columns);

    std::ranges::transform(*this, matrix, result.begin(), [](const auto &t, const auto &u) { return t / u; });
    return result;
}

template <Storable T>
template <MultipliableAssignable<T> U>
decltype(auto) Matrix<T>::hadamardMulAssign(const Matrix<U> &matrix)
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t * u; });

    return *this;
}

template <Storable T>
template <MultipliableAssignable<T> U>
decltype(auto) Matrix<T>::hadamardDivAssign(const Matrix<U> &matrix)
{
    validateOtherMatrixSize(matrix.getRows(), matrix.getColumns(), __FILE_NAME__, __FUNCTION__, __LINE__);

    std::ranges::transform(*this, matrix, begin(), [](const auto &t, const auto &u) { return t / u; });

    return *this;
}

#pragma endregion

#pragma region default matrices

template <Storable T>
Matrix<T> Matrix<T>::identity(size_t size)
    requires HasIdentityElement<T> && HasZeroElement<T>
{
    return diagonal(size, value_type{1});
}

template <Storable T>
Matrix<T> Matrix<T>::zero(size_t rows, size_t columns)
    requires HasZeroElement<T>
{
    return fill(rows, columns, value_type{0});
}

template <Storable T>
Matrix<T> Matrix<T>::fill(size_t rows, size_t columns, const value_type &fill)
{
    Matrix<T> zeroMatrix(rows, columns);
    std::ranges::fill(zeroMatrix, fill);

    return zeroMatrix;
}

template <Storable T>
Matrix<T> Matrix<T>::diagonal(size_t size, const value_type &fill)
    requires HasZeroElement<T>
{
    Matrix<T> diagonalMatrix = Matrix<T>::zero(size, size);

    std::ranges::for_each(std::views::iota(0u, size),
                          [&](auto index) { diagonalMatrix(index, index) = value_type{fill}; });

    return diagonalMatrix;
}

#pragma endregion

#pragma region other

template <Storable T>
auto Matrix<T>::det() const
    requires DeterminantComputable<T>
{
    validateSquareSize(__FILE_NAME__, __FUNCTION__, __LINE__);

    if (isLinearDependent())
        return value_type{0};

    Matrix<T> temp(*this);

    size_t n = rows;
    for (size_t k = 0; k < n - 1; ++k)
    {
        for (size_t i = k + 1; i < n; ++i)
        {
            for (size_t j = k + 1; j < n; ++j)
            {
                temp(i, j) = (temp(k, k) * temp(i, j) - temp(i, k) * temp(k, j));
                if (k > 0)
                    temp(i, j) /= temp(k - 1, k - 1);
            }
        }
    }

    return temp(rows - 1, columns - 1);
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
        throw NotInvertible(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

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

    std::ranges::transform(std::views::iota(0u, getSize()), transposed.begin(), [&](auto index) {
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
    validateSquareSize(__FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateSquareSize(__FILE_NAME__, __FUNCTION__, __LINE__);

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

#pragma endregion

#pragma region size management

template <Storable T>
Matrix<T> &Matrix<T>::removeRow(size_t row)
{
    validateRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);

    auto oldData = data;
    size_t oldRows = rows;
    this->rows--;

    allocateMemory(getSize());

    size_t currentRow = 0;
    for (size_t i = 0; i < oldRows; ++i)
    {
        if (i == row)
            continue;

        for (size_t j = 0; j < columns; ++j)
            data[currentRow * columns + j] = oldData[i * columns + j];

        currentRow++;
    }

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::removeColumn(size_t column)
{
    validateColumn(column, __FILE_NAME__, __FUNCTION__, __LINE__);

    size_t oldColumns = columns;
    auto oldData = data;
    this->columns--;

    allocateMemory(getSize());

    for (size_t i = 0; i < rows; ++i)
    {
        size_t rowIndex = i * oldColumns;

        size_t currentColumn = 0;
        for (size_t j = 0; j < oldColumns; ++j)
        {
            if (j == column)
                continue;

            data[rowIndex + currentColumn] = oldData[rowIndex + j];

            currentColumn++;
        }
    }

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::insertRow(size_t row)
    requires HasZeroElement<T>
{
    return insertRow(row, value_type{0});
}

template <Storable T>
Matrix<T> &Matrix<T>::insertRow(size_t row, const value_type &fill)
{
    validateInsertRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);

    auto oldData = data;
    this->rows++;

    allocateMemory(getSize());

    size_t currentRow = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
            data[i * columns + j] = i == row ? value_type{fill} : oldData[currentRow * columns + j];

        if (i != row)
            currentRow++;
    }

    return *this;
}

template <Storable T>
template <Iterable C>
Matrix<T> &Matrix<T>::insertRow(size_t row, const C &container)
{
    validateInsertRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);

    auto oldData = data;
    this->rows++;

    allocateMemory(getSize());

    if (std::ranges::distance(container) != columns)
        throw InsertContainerInvalidSize(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    auto it = container.begin();

    size_t currentRow = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
            data[i * columns + j] = i == row ? value_type{*(it++)} : oldData[currentRow * columns + j];

        if (i != row)
            currentRow++;
    }

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::insertColumn(size_t column)
    requires HasZeroElement<T>
{
    return insertColumn(column, value_type{0});
}

template <Storable T>
Matrix<T> &Matrix<T>::insertColumn(size_t column, const value_type &fill)
{
    validateInsertColumn(column, __FILE_NAME__, __FUNCTION__, __LINE__);

    auto oldData = data;
    size_t oldColumns = columns;
    this->columns++;

    allocateMemory(getSize());

    for (size_t i = 0; i < rows; ++i)
    {
        size_t currentColumn = 0;
        for (size_t j = 0; j < columns; ++j)
        {
            data[i * columns + j] = j == column ? value_type{fill} : oldData[i * oldColumns + currentColumn];

            if (j != column)
                currentColumn++;
        }
    }

    return *this;
}

template <Storable T>
template <Iterable C>
Matrix<T> &Matrix<T>::insertColumn(size_t column, const C &container)
{
    validateInsertColumn(column, __FILE_NAME__, __FUNCTION__, __LINE__);

    auto oldData = data;
    size_t oldColumns = columns;
    this->columns++;

    allocateMemory(getSize());

    if (std::ranges::distance(container) != rows)
        throw InsertContainerInvalidSize(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));

    auto it = container.begin();

    for (size_t i = 0; i < rows; ++i)
    {
        size_t currentColumn = 0;
        for (size_t j = 0; j < columns; ++j)
        {
            data[i * columns + j] = j == column ? value_type{*(it++)} : oldData[oldColumns * i + currentColumn];

            if (j != column)
                currentColumn++;
        }
    }

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::swapRows(size_t first, size_t second)
{
    validateRow(first, __FILE_NAME__, __FUNCTION__, __LINE__);
    validateRow(second, __FILE_NAME__, __FUNCTION__, __LINE__);

    if (first == second)
        return *this;

    std::ranges::swap_ranges(begin() + first * columns, begin() + first * columns + columns, begin() + second * columns,
                             begin() + second * columns + columns);

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::swapColumns(size_t first, size_t second)
{
    validateColumn(first, __FILE_NAME__, __FUNCTION__, __LINE__);
    validateColumn(second, __FILE_NAME__, __FUNCTION__, __LINE__);

    if (first == second)
        return *this;

    for (size_t i = 0; i < rows; ++i)
    {
        std::swap(at(i, first), at(i, second));
    }

    return *this;
}

template <Storable T>
Matrix<T> &Matrix<T>::reshape(size_t rows, size_t columns)
    requires HasZeroElement<T>
{
    return reshape(rows, columns, value_type{0});
}

template <Storable T>
Matrix<T> &Matrix<T>::reshape(size_t rows, size_t columns, const value_type &fill)
{
    validateMatrixSize(rows, columns, __FILE_NAME__, __FUNCTION__, __LINE__);

    size_t oldRows = this->rows;
    size_t oldColumns = this->columns;

    this->rows = rows;
    this->columns = columns;

    auto oldData = data;

    allocateMemory(getSize());

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            data[i * columns + j] = (i > oldRows || j > oldColumns) ? value_type{fill} : oldData[i * oldColumns + j];

    return *this;
}

#pragma endregion

#pragma region lookup

template <Storable T>
Matrix<T>::Row Matrix<T>::operator[](size_t row)
{
    validateRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);

    return Row(*this, row);
}

template <Storable T>
const Matrix<T>::Row Matrix<T>::operator[](size_t row) const
{
    validateRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);

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
    validateRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);
    validateColumn(column, __FILE_NAME__, __FUNCTION__, __LINE__);

    return data[row * columns + column];
}

template <Storable T>
auto Matrix<T>::at(size_t row, size_t column) const -> const_reference
{
    validateRow(row, __FILE_NAME__, __FUNCTION__, __LINE__);
    validateColumn(column, __FILE_NAME__, __FUNCTION__, __LINE__);

    return data[row * columns + column];
}

#pragma endregion

#pragma region compare

template <Storable T>
bool Matrix<T>::equalsShape(const Matrix<T> &matrix) const noexcept
{
    return matrix.getRows() == rows && matrix.getColumns() == columns;
}

template <Storable T>
bool Matrix<T>::hasLinearDependentRows() const
{
    for (size_t row1 = 0; row1 < rows; ++row1)
    {
        for (size_t row2 = 0; row2 < rows; ++row2)
        {
            if (row1 == row2 || at(row2, 0) == value_type{0})
                continue;

            auto mult = at(row1, 0) / at(row2, 0);
            bool dependent = true;
            for (size_t j = 1; j < columns; ++j)
            {
                auto value = at(row2, j);
                if (value == value_type{0} || at(row1, j) / value != mult)
                {
                    dependent = false;
                    break;
                }
            }

            if (dependent)
                return true;
        }
    }

    return false;
}

template <Storable T>
bool Matrix<T>::hasLinearDependentRows() const
    requires std::is_arithmetic_v<T>
{
    for (size_t row1 = 0; row1 < rows; ++row1)
    {
        for (size_t row2 = 0; row2 < rows; ++row2)
        {
            if (row1 == row2 || abs(at(row2, 0)) <= std::numeric_limits<T>::epsilon())
                continue;

            double mult = static_cast<double>(at(row1, 0)) / at(row2, 0);
            bool dependent = true;
            for (size_t j = 1; j < columns; ++j)
            {
                auto value = at(row2, j);
                if (value == value_type{0} || at(row1, j) / value != mult)
                {
                    dependent = false;
                    break;
                }
            }

            if (dependent)
                return true;
        }
    }

    return false;
}

template <Storable T>
bool Matrix<T>::hasLinearDependentColumns() const
{
    for (size_t col1 = 0; col1 < columns; ++col1)
    {
        for (size_t col2 = 0; col2 < columns; ++col2)
        {
            if (col1 == col2 || at(0, col2) == value_type{0})
                continue;

            auto mult = at(0, col1) / at(0, col2);
            bool dependent = true;
            for (size_t j = 1; j < rows; ++j)
            {
                auto value = at(j, col2);
                if (value == value_type{0} || at(j, col1) / value != mult)
                {
                    dependent = false;
                    break;
                }
            }

            if (dependent)
                return true;
        }
    }

    return false;
}

template <Storable T>
bool Matrix<T>::hasLinearDependentColumns() const
    requires std::is_arithmetic_v<T>
{
    for (size_t col1 = 0; col1 < columns; ++col1)
    {
        for (size_t col2 = 0; col2 < columns; ++col2)
        {
            if (col1 == col2 || abs(at(0, col2)) <= std::numeric_limits<T>::epsilon())
                continue;

            double mult = static_cast<double>(at(0, col1)) / at(0, col2);
            bool dependent = true;
            for (size_t j = 1; j < rows; ++j)
            {
                auto value = at(j, col2);
                if (value == value_type{0} || at(j, col1) / value != mult)
                {
                    dependent = false;
                    break;
                }
            }

            if (dependent)
                return true;
        }
    }

    return false;
}

template <Storable T>
bool Matrix<T>::isLinearDependent() const
{
    return this->hasLinearDependentColumns() || this->hasLinearDependentRows();
}

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
    return std::ranges::all_of(std::views::iota(0u, getSize()), [&](size_t index) {
        size_t i = index / columns;
        size_t j = index % columns;

        if (i == j)
            return data[index] == value_type{1};
        return data[index] == value_type{0};
    });
}

template <Storable T>
bool Matrix<T>::isIdentity() const
    requires HasIdentityElement<T> && std::is_floating_point_v<T>
{
    if (rows != columns)
        return false;

    size_t n = getRows();
    return std::ranges::all_of(std::views::iota(0u, getSize()), [&](size_t index) {
        size_t i = index / columns;
        size_t j = index % columns;

        if (i == j)
            return std::abs(data[index] - value_type{1}) <= std::numeric_limits<T>::epsilon();
        return std::abs(data[index]) <= std::numeric_limits<T>::epsilon();
    });
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::equals(const Matrix<U> &matrix) const
{
    if (!equalsShape(matrix))
        return false;

    return std::ranges::equal(*this, matrix);
}

template <Storable T>
bool Matrix<T>::equals(const Matrix<T> &matrix) const
{
    if (!equalsShape(matrix))
        return false;

    return std::ranges::equal(*this, matrix);
}

template <Storable T>
bool Matrix<T>::equals(const Matrix<T> &matrix) const
    requires std::is_floating_point_v<T>
{
    if (!equalsShape(matrix))
        return false;

    return std::ranges::all_of(*this, matrix, [](const auto &t, const auto &m) {
        return std::abs(t - m) <= std::numeric_limits<value_type>::epsilon();
    });
}

template <Storable T>
template <EqualityComparable<T> U>
bool Matrix<T>::operator==(const Matrix<U> &matrix) const
{
    return equals(matrix);
}

template <Storable T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) const
{
    return equals(matrix);
}

template <Storable T>
bool Matrix<T>::operator==(const Matrix<T> &matrix) const
    requires std::is_floating_point_v<T>
{
    return equals(matrix);
}

#pragma endregion

template <Storable T>
void Matrix<T>::validateMatrixSize(size_t rows, size_t columns, const char *filename, const char *function, int line)
{
    if (rows <= 0 || columns <= 0)
        throw MatrixInvalidShape(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateOtherMatrixSize(size_t rows, size_t columns, const char *filename, const char *function,
                                        int line) const
{
    if (rows != this->rows || columns != this->columns)
        throw MatricesNotEqualSize(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateRow(size_t row, const char *filename, const char *function, int line) const
{
    if (row < 0 || row >= rows)
        throw MatrixRowOutOfBounds(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateColumn(size_t column, const char *filename, const char *function, int line) const
{
    if (column < 0 || column >= columns)
        throw MatrixColumnOutOfBounds(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateInsertRow(size_t row, const char *filename, const char *function, int line) const
{
    if (row < 0 || row > rows)
        throw MatrixRowOutOfBounds(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateInsertColumn(size_t column, const char *filename, const char *function, int line) const
{
    if (column < 0 || column > columns)
        throw MatrixColumnOutOfBounds(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::validateSquareSize(const char *filename, const char *function, int line) const
{
    if (!isSquare())
        throw DeterminantNotSquareMatrix(filename, function, line, time(nullptr));
}

template <Storable T>
void Matrix<T>::allocateMemory(size_t elements)
{
    try
    {
        this->data = std::make_shared<T[]>(elements);
    }
    catch (std::bad_alloc err)
    {
        throw MatrixBadAlloc(__FILE_NAME__, __FUNCTION__, __LINE__, time(nullptr));
    }
}
