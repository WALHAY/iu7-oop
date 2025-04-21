#pragma once

#include "base/BaseMatrix.hpp"
#include <memory>

template <typename T>
class Matrix : public BaseMatrix
{
  public:
    using value_type = T;
    using size_type = std::size_t;

#pragma region constructors
    Matrix(size_t rows, size_t columns);
	Matrix(std::initializer_list<std::initializer_list<T>> ilist);
#pragma endregion

    ~Matrix() override = default;

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

#include "matrix/Matrix.hpp"
