#pragma once

#include "base/BaseMatrix.hpp"
#include "matrix/MatrixConcepts.hpp"
#include "matrix/iterators/ConstMatrixIterator.hpp"
#include "matrix/iterators/ConstReverseMatrixIterator.hpp"
#include "matrix/iterators/MatrixIterator.hpp"
#include "matrix/iterators/ReverseMatrixIterator.hpp"
#include <memory>

template <Storable T>
class Matrix : public BaseMatrix
{
    class Row;
    friend class MatrixIterator<T>;
    friend class ConstMatrixIterator<T>;

  public:
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator = MatrixIterator<T>;
    using const_pointer = const T *;
    using const_reference = const T &;
    using const_iterator = ConstMatrixIterator<T>;
    using reverse_iterator = ReverseMatrixIterator<T>;
    using const_reverse_iterator = ConstReverseMatrixIterator<T>;

#pragma region constructors
    Matrix(size_t rows, size_t columns);
    explicit Matrix(size_t size);

    template <ConvertibleTo<T> U>
    Matrix(const U *value, size_t rows, size_t columns);
    Matrix(const T *value, size_t rows, size_t columns);

    template <std::ranges::input_range R>
        requires ConvertibleTo<std::ranges::range_value_t<R>, T>
    Matrix(const R range, size_t rows, size_t columns);

    template <ConvertibleTo<T> U>
    Matrix(std::initializer_list<std::initializer_list<U>> ilist);
    Matrix(std::initializer_list<std::initializer_list<T>> ilist);

    template <ConvertibleTo<T> U>
    Matrix(const Matrix<U> &matrix);
    Matrix(const Matrix<T> &matrix);

    template <ConvertibleTo<T> U>
    Matrix(Matrix<U> &&matrix);
    Matrix(Matrix<T> &&matrix) noexcept = default;
#pragma endregion

#pragma region assign

    ~Matrix() override = default;

    template <ConvertibleTo<T> U>
    Matrix<T> &operator=(const Matrix<U> &matrix);
    Matrix<T> &operator=(const Matrix<T> &matrix);

    template <ConvertibleTo<T> U>
    Matrix<T> &operator=(Matrix<U> &&matrix);
    Matrix<T> &operator=(Matrix<T> &&matrix) noexcept = default;

#pragma endregion

#pragma region iterators
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
#pragma endregion

#pragma region addition

    template <AddableTo<T> U>
    decltype(auto) add(const U &value) const;

    template <AddableTo<T> U>
    decltype(auto) add(const Matrix<U> &matrix) const;

    template <AddableAssignable<T> U>
    Matrix<T> &addAssign(const U &value);

    template <AddableAssignable<T> U>
    Matrix<T> &addAssign(const Matrix<U> &matrix);

    template <AddableTo<T> U>
    decltype(auto) operator+(const U &value) const;

    template <AddableTo<T> U>
    decltype(auto) operator+(const Matrix<U> &matrix) const;

    template <AddableAssignable<T> U>
    Matrix<T> &operator+=(const U &value);

    template <AddableAssignable<T> U>
    Matrix<T> &operator+=(const Matrix<U> &matrix);

#pragma endregion

#pragma region subtraction

    template <SubtractableTo<T> U>
    decltype(auto) sub(const U &value) const;

    template <SubtractableTo<T> U>
    decltype(auto) sub(const Matrix<U> &matrix) const;

    template <SubtractableAssignable<T> U>
    Matrix<T> &subAssign(const U &value);

    template <SubtractableAssignable<T> U>
    Matrix<T> &subAssign(const Matrix<U> &matrix);

    template <SubtractableTo<T> U>
    decltype(auto) operator-(const U &value) const;

    template <SubtractableTo<T> U>
    decltype(auto) operator-(const Matrix<U> &matrix) const;

    template <SubtractableAssignable<T> U>
    Matrix<T> &operator-=(const U &value);

    template <SubtractableAssignable<T> U>
    Matrix<T> &operator-=(const Matrix<U> &matrix);

#pragma endregion

#pragma region multiplication

    template <MultipliableTo<T> U>
    decltype(auto) mul(const U &value) const;

    template <MultipliableTo<T> U>
    decltype(auto) mul(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    Matrix<T> &mulAssign(const U &value);

    template <MultipliableAssignable<T> U>
    Matrix<T> &mulAssign(const Matrix<U> &matrix);

    template <MultipliableTo<T> U>
    decltype(auto) operator*(const U &value) const;

    template <MultipliableTo<T> U>
    decltype(auto) operator*(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    Matrix<T> &operator*=(const U &value);

    template <MultipliableAssignable<T> U>
    Matrix<T> &operator*=(const Matrix<U> &matrix);

#pragma endregion

#pragma region division

    template <MultipliableTo<T> U>
    decltype(auto) div(const U &value) const;

    template <MultipliableTo<T> U>
    decltype(auto) div(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    Matrix<T> &divAssign(const U &value);

    template <MultipliableAssignable<T> U>
    Matrix<T> &divAssign(const Matrix<U> &matrix);

    template <MultipliableTo<T> U>
    decltype(auto) operator/(const U &value) const;

    template <MultipliableTo<T> U>
    decltype(auto) operator/(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    Matrix<T> &operator/=(const U &value);

    template <MultipliableAssignable<T> U>
    Matrix<T> &operator/=(const Matrix<U> &matrix);

#pragma endregion

#pragma region hadamard

    template <MultipliableAssignable<T> U>
    decltype(auto) hadamardMul(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    decltype(auto) hadamardDiv(const Matrix<U> &matrix) const;

    template <MultipliableAssignable<T> U>
    decltype(auto) hadamardMulAssign(const Matrix<U> &matrix);

    template <MultipliableAssignable<T> U>
    decltype(auto) hadamardDivAssign(const Matrix<U> &matrix);

#pragma endregion

#pragma region default matrices

    static Matrix<T> identity(size_t size)
        requires HasIdentityElement<T> && HasZeroElement<T>;
    static Matrix<T> zero(size_t rows, size_t columns)
        requires HasZeroElement<T>;

    static Matrix<T> fill(size_t rows, size_t columns, const value_type &fill);
    static Matrix<T> diagonal(size_t size, const value_type &fill) requires HasZeroElement<T>;

#pragma endregion

#pragma region misc
    auto det() const
        requires DeterminantComputable<T>;

    Matrix<T> transpose() const;

    bool invertible() const;

    decltype(auto) operator~() const
        requires InvertComputable<T>;
    decltype(auto) operator~() const
        requires InvertComputable<T> && std::is_arithmetic_v<T>;

    decltype(auto) invert() const
        requires InvertComputable<T>;
    decltype(auto) invert() const
        requires InvertComputable<T> && std::is_arithmetic_v<T>;

    std::pair<Matrix<T>, Matrix<T>> LU() const
        requires LUComputable<T>;
    std::pair<Matrix<double>, Matrix<double>> LU() const
        requires LUComputable<T> && std::is_arithmetic_v<T>;

#pragma endregion

#pragma region size management

    Matrix<T> &removeRow(size_t column);
    Matrix<T> &removeColumn(size_t column);

    Matrix<T> &insertRow(size_t row)
        requires HasZeroElement<T>;
    Matrix<T> &insertRow(size_t row, const value_type &fill);
    template <Container C>
    Matrix<T> &insertRow(size_t row, const C &container);

    Matrix<T> &insertColumn(size_t column)
        requires HasZeroElement<T>;
    Matrix<T> &insertColumn(size_t column, const value_type &fill);
    template <Container C>
    Matrix<T> &insertColumn(size_t row, const C &container);

    Matrix<T> &swapRows(size_t first, size_t second);
    Matrix<T> &swapColumns(size_t first, size_t second);

    Matrix<T> &reshape(size_t rows, size_t cols)
        requires HasZeroElement<T>;
    Matrix<T> &reshape(size_t rows, size_t cols, const value_type &fill);

#pragma endregion

#pragma region lookup

    Row operator[](size_t row);
    const Row operator[](size_t row) const;

    reference operator()(size_t row, size_t column);
    const_reference operator()(size_t row, size_t column) const;

    reference at(size_t row, size_t column);
    const_reference at(size_t row, size_t column) const;

#pragma endregion

#pragma region compare

    bool isZero() const
        requires HasZeroElement<T>;
    bool isZero() const
        requires HasZeroElement<T> && std::is_floating_point_v<T>;

    bool isIdentity() const
        requires HasIdentityElement<T>;
    bool isIdentity() const
        requires HasIdentityElement<T> && std::is_floating_point_v<T>;

    bool equals(Matrix<T> &matrix) const;
    bool equals(Matrix<T> &matrix) const requires std::is_floating_point_v<T>;

    bool operator==(Matrix<T> &matrix) const;
    bool operator==(Matrix<T> &matrix) const
        requires std::is_floating_point_v<T>;

#pragma endregion

  protected:
    void validateMatrixSize(size_t rows, size_t columns);
    void validateOtherMatrixSize(size_t rows, size_t columns, int line) const;
    void validateRow(size_t row, int line) const;

    void validateColumn(size_t column, int line) const;
    void validateInsertRow(size_t row, int line) const;

    void validateInsertColumn(size_t column, int line) const;
    void validateSquareSize(int line) const;

    void allocateMemory(size_t elements);

    std::shared_ptr<T[]> data;

  private:
    class Row
    {
      public:
        Row(const Matrix<T> &matrix, size_t row) noexcept;

        Row(const Row &) = delete;
        Row(Row &&) = delete;

        Row &operator=(const Row &) = delete;
        Row &operator=(Row &&) = delete;

        T &operator[](size_t index);
        const T &operator[](size_t index) const;

      private:
        const Matrix<T> &matrix;
        const size_t row;
    };
};

#include <matrix/MatrixImpl.hpp>
#include <matrix/MatrixRow.hpp>
