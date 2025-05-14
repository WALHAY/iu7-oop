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

void testAdd() {
	std::cout << "----- ADDITION -----\n\n";
	Matrix<int> im = {{1, 2}, {3, 4}};
	Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

	std::cout << "M1:\n";
	printMatrix(im);
	std::cout << "\n";

	std::cout << "M2:\n";
	printMatrix(dm);
	std::cout << "\n";

	std::cout << "M1 + M2:\n";
	printMatrix(im + dm);
	std::cout << "\n";

	std::cout << "M2 + M1:\n";
	printMatrix(dm + im);
	std::cout << "\n";

	Matrix<int> imm(im);
	std::cout << "M1 += M2:\n";
	im += dm;
	printMatrix(im);
	std::cout << "\n";

	std::cout << "M2 += M1:\n";
	dm += imm;
	printMatrix(dm);
	std::cout << "\n";
}

void testSub() {
	Matrix<int> im = {{1, 2}, {3, 4}};
	Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

	std::cout << "----- SUBTRACTION -----\n\n";
	std::cout << "M1:\n";
	printMatrix(im);
	std::cout << "\n";

	std::cout << "M2:\n";
	printMatrix(dm);
	std::cout << "\n";

	std::cout << "M1 - M2:\n";
	printMatrix(im - dm);
	std::cout << "\n";

	std::cout << "M2 - M1:\n";
	printMatrix(dm - im);
	std::cout << "\n";

	Matrix<int> imm(im);
	std::cout << "M1 -= M2:\n";
	im -= dm;
	printMatrix(im);
	std::cout << "\n";

	std::cout << "M2 -= M1:\n";
	dm -= imm;
	printMatrix(dm);
	std::cout << "\n";
}

int main()
{
	testAdd();
	testSub();
    return 0;
}
