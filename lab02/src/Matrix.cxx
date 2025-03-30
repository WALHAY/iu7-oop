#include "../inc/Matrix.hpp"
#include <algorithm>
#include <exception>
#include <initializer_list>
#include <ranges>
#include <utility>

template <typename Type> Matrix<Type>::Matrix()
{
    this->rows = 0;
    this->columns = 0;
}

template <typename Type> Matrix<Type>::Matrix(std::initializer_list<std::initializer_list<Type>> matrix)
{
    std::size_t rows = matrix.size();
    if (rows <= 0)
        throw std::exception();

    std::ranges::for_each(matrix, [this](std::initializer_list<Type> list) { this->data.push_back(std::vector<Type>(list.begin(), list.end())); });
}

template <typename Type> Matrix<Type>::~Matrix()
{
}

template <typename Type> void Matrix<Type>::resize(std::size_t rows, std::size_t columns)
{
    std::ranges::for_each(this->data, [&columns](std::vector<Type> &v) { v.resize(columns, Type()); });
    this->data.resize(rows, std::vector<Type>(columns, Type()));
}

template <typename Type> Type Matrix<Type>::at(std::size_t row, std::size_t column)
{
    try
    {
        return this->data.at(row).at(column);
    }
    catch (std::exception &e)
    {
        throw e;
    }
}

template <typename Type> void Matrix<Type>::print()
{
    for (auto row : this->data)
    {
        for (auto i : row)
            std::cout << i << " ";
        std::cout << "\n";
    }
}

template<typename Type>
Matrix<Type> Matrix<Type>::add(Type value)
{
}


/*template<typename Type>*/
/*Matrix<Type> Matrix<Type>::add_matrix(Matrix<Type> matrix)*/
/*{*/
/*	return Matrix<Type>();*/
/*}*/

template class Matrix<int>;
