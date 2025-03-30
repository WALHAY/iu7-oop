#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>

template<typename Type>
class Matrix {
	private:
		std::size_t rows;
		std::size_t columns;

		std::vector<std::vector<Type>> data;

	public:
		Matrix() noexcept;
		explicit Matrix(Matrix<Type> &matrix);
		Matrix(const std::size_t rows, const std::size_t cols);
		Matrix(Type **matrix, const std::size_t rows, const std::size_t cols);
		Matrix(Matrix<Type> &&matrix);
		Matrix(const std::initializer_list<std::initializer_list<Type>> list);

		~Matrix() = default;

		/*
		 * INDEXATION
		 */
		Type& at(const std::size_t row, const std::size_t column);
		const Type& at(const std::size_t row, const std::size_t column) const;
		Type& operator ()(const std::size_t row, const std::size_t column);
		const Type& operator ()(const std::size_t row, const std::size_t column) const;

		/*
		 * SIMPLE ADDITION
		 */
		Matrix<Type> add(const Type &value) const;
		Matrix<Type> operator+(const Type &value) const;
		Matrix<Type>& operator+=(const Type &value);

		/*
		 * COMPLEX ADDITION
		 */
		Matrix<Type> add_matrix(const Matrix<Type> &matrix) const;
		Matrix<Type> operator+(const Matrix<Type> &matrix) const;
		Matrix<Type>& operator+=(const Matrix<Type> &matrix);

		/*
		 * SIMPLE SUB
		 */
		Matrix<Type> sub(const Type &value) const;
		Matrix<Type> operator-(const Type &value) const;
		Matrix<Type>& operator-=(const Type &value);

		/*
		 * COMPLEX SUB
		 */
		Matrix<Type> sub_matrix(const Matrix<Type> &matrix) const;
		Matrix<Type> operator-(const Matrix<Type> &matrix) const;
		Matrix<Type>& operator-=(const Matrix<Type> &matrix);

		/*
		 * DETERMINANT
		 */
		Type determinant() const;

		/*
		 * MISCELLANOUS
		 */
		void resize(std::size_t rows, std::size_t columns);

		void print();

		Type determinant();
};
