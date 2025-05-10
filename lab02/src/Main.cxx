#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
	Matrix<double> zero = Matrix<double>::identity(5);
    Matrix<double> dm = {{1, 1}, {1, 0}};

    for (const auto &it : dm.invert())
        std::cout << it << " ";

	std::cout << "is zero: " << zero.isIdentity();
    return 0;
}
