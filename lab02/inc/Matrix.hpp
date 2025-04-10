#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include "BaseMatrix.hpp"
#include "MatrixExceptions.hpp"

template<typename T>
class Matrix : public BaseMatrix {
	private:
		std::shared_ptr<T[]> data = nullptr;

	public:
		Matrix() noexcept;
		explicit Matrix(Matrix<T> &matrix) noexcept;
		Matrix(const size_t rows, const size_t cols) noexcept;
		Matrix(T **matrix, const size_t rows, const size_t cols) noexcept;
		Matrix(Matrix<T> &&matrix)noexcept;
		Matrix(const std::initializer_list<std::initializer_list<T>> list) noexcept;

		~Matrix() = default;

		/*
		 * INDEXATION
		 */
		T& at(const size_t row, const size_t column);
		const T& at(const size_t row, const size_t column) const;
		T& operator ()(const size_t row, const size_t column);
		const T& operator ()(const size_t row, const size_t column) const;

		/*
		 * SIMPLE ADDITION
		 */
		Matrix<T> add(const T &value) const;
		Matrix<T> operator+(const T &value) const;
		Matrix<T>& operator+=(const T &value);

		/*
		 * COMPLEX ADDITION
		 */
		Matrix<T> addMatrix(const Matrix<T> &matrix) const;
		Matrix<T> operator+(const Matrix<T> &matrix) const;
		Matrix<T>& operator+=(const Matrix<T> &matrix);

		/*
		 * SIMPLE SUB
		 */
		Matrix<T> sub(const T &value) const;
		Matrix<T> operator-(const T &value) const;
		Matrix<T>& operator-=(const T &value);

		/*
		 * COMPLEX SUB
		 */
		Matrix<T> subMatrix(const Matrix<T> &matrix) const;
		Matrix<T> operator-(const Matrix<T> &matrix) const;
		Matrix<T>& operator-=(const Matrix<T> &matrix);

		/*
		 * DETERMINANT
		 */
		T determinant() const;

		/*
		 * MISCELLANOUS
		 */
		void resize(size_t rows, size_t columns);

private:

		void allocateMemory(size_t rows, size_t columns);

		void validateRow(const size_t row) const;
		void validateColumn(const size_t column) const;
};
