#pragma once

#include "base/BaseMatrix.hpp"
#include "matrix/MatrixConcepts.hpp"
#include "matrix/iterators/ConstMatrixIterator.hpp"
#include "matrix/iterators/MatrixIterator.hpp"
#include <memory>

template <Storable T>
class Matrix : public BaseMatrix
{
	friend class MatrixIterator<T>;
	friend class ConstMatrixIterator<T>;
  public:
    using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator = MatrixIterator<T>;
	using const_iterator = ConstMatrixIterator<T>;
    using size_type = std::size_t;

#pragma region constructors
    Matrix(size_t rows, size_t columns);
	Matrix(std::initializer_list<std::initializer_list<T>> ilist);
	Matrix(const Matrix<T> &matrix);
	Matrix(Matrix<T> &&matrix) noexcept = default;
#pragma endregion

    ~Matrix() override = default;

#pragma region iterators
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

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
