#pragma once

#include <cstddef>
#include <initializer_list>
#include <vector>
#include <iostream>

template<typename Type>
class Matrix {
	private:
		std::size_t rows;
		std::size_t columns;

		std::vector<std::vector<Type>> data;

	public:
		Matrix();
		Matrix(std::initializer_list<std::initializer_list<Type>> list);

		~Matrix();

		Type at(std::size_t row, std::size_t column);

		void resize(std::size_t rows, std::size_t columns);

		void print();

		Matrix<Type> add(Type add); 
		/*Matrix<Type> add_matrix(Matrix<Type> matrix);*/
};
