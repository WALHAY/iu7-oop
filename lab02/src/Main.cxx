#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix im = {{5, 2}, {3, 7}};
	Matrix dm = {
		{-0.5, 0.5},
		{0.5, -0.5}
	};

	im += dm;

    std::cout << "mx[1][1]: " << im[1][1] << std::endl;

	std:: cout << "det: " << im.det() << std::endl;

    for (const auto &it : im)
        std::cout << it << " ";
    return 0;
}
