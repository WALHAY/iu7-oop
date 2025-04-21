#pragma once

#include "base/BaseMatrix.hpp"
#include "matrix/iterators/MatrixIterator.hpp"
#include <memory>

template <typename T>
class Matrix : public BaseMatrix
{
	friend class MatrixIterator<T>;
  public:
    using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator = MatrixIterator<T>;
    using size_type = std::size_t;

#pragma region constructors
    Matrix(size_t rows, size_t columns);
	Matrix(std::initializer_list<std::initializer_list<T>> ilist);
	Matrix(Matrix<T> &&matrix) noexcept = default;
#pragma endregion

    ~Matrix() override = default;

#pragma region iterators
	iterator begin();
	iterator end();

#pragma endregion

#pragma region addition
    template <typename U>
    Matrix<decltype(T() + U())> operator+(const U &value) const;

    template <typename U>
    Matrix<decltype(T() + U())> &operator+=(const U &value);

    template <typename U>
    Matrix<decltype(T() + U())> operator+(const Matrix<U> &matrix) const;

    template <typename U>
    Matrix<decltype(T() + U())> &operator+=(const Matrix<U> &matrix);
#pragma endregion

#pragma region subtraction
    template <typename U>
    Matrix<decltype(T() - U())> operator-(const U &value) const;

    template <typename U>
    Matrix<decltype(T() - U())> &operator-=(const U &value);

    template <typename U>
    Matrix<decltype(T() - U())> operator-(const Matrix<U> &matrix) const;

    template <typename U>
    Matrix<decltype(T() - U())> &operator-=(const Matrix<U> &matrix);
#pragma endregion

#pragma region misc
    // ...
#pragma endregion

  protected:
    std::shared_ptr<T[]> data;

    size_t rows;
    size_t columns;
};

#include <matrix/MatrxImpl.hpp>
