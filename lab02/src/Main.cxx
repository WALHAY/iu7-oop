#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix im = {{1, 2}, {3, 4}};
	Matrix dm = {
		{-0.5, 0.5},
		{0.5, -0.5}
	};

    std::cout << "mx[1][1]: " << im[1][1] << std::endl;

    for (const auto &it : im + dm)
        std::cout << it << " ";
    return 0;
}
