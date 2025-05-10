#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix<double> dm = {{1, 1}, {1, 0}};

    for (const auto &it : dm.invert())
        std::cout << it << " ";
    return 0;
}
