#pragma once

#include "base/BaseMatrix.hpp"
#include "matrix/MatrixConcepts.hpp"
#include "matrix/iterators/ConstMatrixIterator.hpp"
#include "matrix/iterators/MatrixIterator.hpp"
#include <memory>

template <Storable T>
class Matrix : public BaseMatrix
{
    class RowProxy;
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

#pragma region constructors
    Matrix(size_t rows, size_t columns);
    explicit Matrix(size_t size);

    template <ConvertibleTo<T> U>
    Matrix(const U *value, size_t rows, size_t columns);
    Matrix(const T *value, size_t rows, size_t columns);

    template <std::ranges::input_range R>
        requires ConvertibleTo<std::ranges::range_value_t<R>, T>
    Matrix(const R &range, size_t rows, size_t columns);

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

#pragma region misc
    auto det() const
        requires DeterminantComputable<T>;

    static Matrix<T> identity(size_t size)
        requires HasIdentityElement<T> && HasZeroElement<T>;
    static Matrix<T> zero(size_t rows, size_t columns)
        requires HasZeroElement<T>;

    Matrix<T> transpose() const;
    Matrix<T> &transposed();

    decltype(auto) invert() const
        requires InvertComputable<T>;
    decltype(auto) invert() const
        requires InvertComputable<T> && std::is_arithmetic_v<T>;

    void swapRows(size_t first, size_t second);
    void swapColumns(size_t first, size_t second);

    std::pair<Matrix<T>, Matrix<T>> LU() const
        requires LUComputable<T>;
    std::pair<Matrix<double>, Matrix<double>> LU() const
        requires LUComputable<T> && std::is_arithmetic_v<T>;

#pragma endregion

#pragma region lookup

    RowProxy operator[](size_t row);
    const RowProxy operator[](size_t row) const;

    reference operator()(size_t row, size_t column);
    const_reference operator()(size_t row, size_t column) const;

    reference at(size_t row, size_t column);
    const_reference at(size_t row, size_t column) const;

#pragma endregion

#pragma region compare

    bool isZero() const requires HasZeroElement<T>;
    bool isZero() const requires HasZeroElement<T> && std::is_arithmetic_v<T>;

    bool isIdentity() const requires HasIdentityElement<T>;
    bool isIdentity() const requires HasIdentityElement<T> && std::is_arithmetic_v<T>;

	bool equals(Matrix<T> &matrix) const;
    bool operator==(Matrix<T> &matrix) const;

#pragma endregion

  protected:
    void validateEqualSize(size_t rows, size_t columns, int line) const;
    void validateRow(size_t row, int line) const;
    void validateColumn(size_t column, int line) const;
    void validateDeterminantSize(int line) const;

    std::shared_ptr<T[]> data;

  private:
    class RowProxy
    {
      public:
        RowProxy(const Matrix<T> &matrix, size_t row) noexcept;

        RowProxy(const RowProxy &) = delete;
        RowProxy(RowProxy &&) = delete;

        RowProxy &operator=(const RowProxy &) = delete;
        RowProxy &operator=(RowProxy &&) = delete;

        T &operator[](size_t index);
        const T &operator[](size_t index) const;

      private:
        const Matrix<T> &matrix;
        const size_t row;
    };
};

#include <matrix/MatrixImpl.hpp>
#include <matrix/MatrixRowProxy.hpp>
