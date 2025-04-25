#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
    Matrix im = {{5, 2, 1, 4}, {3, 1, 6, 9}};
    Matrix<double> imm = {{5, 0, 1, 4}, {3, 1, 6, 9}};
    Matrix dm = {{-0.5, 0.5}, {0.5, -0.5}};

	im.mulAssign(im.transpose());
    for (size_t i = 0; i < im.getRows(); ++i)
    {
        for (size_t j = 0; j < im.getColumns(); ++j)
        {
            std::cout << im[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
