#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix<double> zero = Matrix<double>::identity(5);
    Matrix<double> dm = {{1, 2, 3}, {4, 5, 6}};

    for (const auto &it : dm.transpose())
        std::cout << it << " ";

    std::cout << "is zero: " << zero.isIdentity();
    return 0;
}
