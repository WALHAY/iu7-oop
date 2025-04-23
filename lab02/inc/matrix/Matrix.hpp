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
    using const_iterator = ConstMatrixIterator<T>;
    using size_type = std::pair<std::size_t, std::size_t>;

#pragma region constructors
    Matrix(size_type size);
    Matrix(std::initializer_list<std::initializer_list<T>> ilist);

	template<ConvertibleTo<T> U>
    Matrix(const Matrix<U> &matrix);

    Matrix(Matrix<T> &&matrix) noexcept = default;
#pragma endregion

    ~Matrix() override = default;

	template<ConvertibleTo<T> U>
	Matrix<T> &operator=(const Matrix<U> &matrix);
	Matrix<T> &operator=(Matrix<T> &&matrix) noexcept = default;

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
    Matrix<decltype(T() + U())> add(const U &value) const;

    template <AddableTo<T> U>
    Matrix<decltype(T() + U())> operator+(const U &value) const;

    template <AddableConvertible<T> U>
    Matrix<T> &operator+=(const U &value);

    template <AddableTo<T> U>
    Matrix<decltype(T() + U())> add(const Matrix<U> &matrix) const;

    template <AddableTo<T> U>
    Matrix<decltype(T() + U())> operator+(const Matrix<U> &matrix) const;

    template <AddableConvertible<T> U>
    Matrix<T> &operator+=(const Matrix<U> &matrix);
#pragma endregion

#pragma region other
    auto det() const;

    static Matrix<T> identity();
    static Matrix<T> zero();

    Matrix<T> transpose() const;
    Matrix<T> invert() const;
#pragma endregion

#pragma region lookup

    RowProxy operator[](size_t row)
    {
        return RowProxy(data, row, size.second);
    }

    const RowProxy operator[](size_t row) const
    {
        return operator[](row);
    }

#pragma endregion

#pragma region misc
    // ...
#pragma endregion

  protected:
    void validateAddSubSize(size_type size, int line) const;

	Matrix<T> matrixExclude(size_t row, size_t columns) const;

    std::shared_ptr<T[]> data;

  private:
    class RowProxy
    {
      public:
        RowProxy(std::shared_ptr<T[]> data, size_t row, size_t matrixColumns)
            : dataPtr(data), row(row), matrixColumns(matrixColumns)
        {
        }

        RowProxy(const RowProxy &) = default;
        RowProxy(RowProxy &&) = default;

        RowProxy &operator=(const RowProxy &) = delete;
        RowProxy &operator=(RowProxy &&) = delete;

        T &operator[](size_t index)
        {
            return dataPtr.lock()[row * matrixColumns + index];
        }

        const T &operator[](size_t index) const
        {
            return *this[index];
        }

      private:
        size_t matrixColumns;
        size_t row;
        std::weak_ptr<T[]> dataPtr;
    };
};

#include <matrix/MatrxImpl.hpp>
