#include "matrix/Matrix.hpp"
#include <iostream>

template<Storable T>
void printMatrix(const Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getColumns(); ++j)
        {
			std::cout << matrix[i][j] << " ";
        }
		 std::cout << "\n";
    }
}

int main()
{
    Matrix<double> zero = Matrix<double>::zero(2, 3);
	zero -= 1;
    Matrix<double> dm = {{1, 2, 3}, {4, 5, 6}};

	printMatrix(dm + zero);

    std::cout << "is zero: " << zero.isIdentity();
    return 0;
}
