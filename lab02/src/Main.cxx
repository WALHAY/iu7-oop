#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix im = {{5, 2, 1}, {3, 1, 6}};
    Matrix dm = {{-0.5, 0.5}, {0.5, -0.5}};

    // im += dm;
	//
	
	auto transposed = im.transpose();

    for (size_t i = 0; i < transposed.getRows(); ++i)
    {
        for (size_t j = 0; j < transposed.getColumns(); ++j)
        {
			 std::cout << transposed[i][j] << " ";
        }
		std::cout << "\n";
    }

    // std::cout << "det: " << im.det() << std::endl;

    // for (const auto &it : im)
    //     std::cout << it << " ";
    return 0;
}
