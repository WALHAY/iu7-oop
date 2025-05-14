#include "matrix/Matrix.hpp"
#include <iostream>

template <Storable T>
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

void testAdd()
{
    std::cout << "----- ADDITION -----\n\n";
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M1 + 1:\n";
    printMatrix(im + 1);
    std::cout << "\n";

    std::cout << "M2 + 1.5:\n";
    printMatrix(im + 1.5);
    std::cout << "\n";

    std::cout << "M1 + M2:\n";
    printMatrix(im + dm);
    std::cout << "\n";

    std::cout << "M2 + M1:\n";
    printMatrix(dm + im);
    std::cout << "\n";

    Matrix<int> imm(im);
    std::cout << "M1 += M2:\n";
    imm += dm;
    printMatrix(imm);
    std::cout << "\n";

    Matrix<double> dmm(dm);
    std::cout << "M2 += M1:\n";
    dmm += im;
    printMatrix(dmm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 += 1:\n";
    imm += 1;
    printMatrix(imm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 += 1.5:\n";
    imm += 1.5;
    printMatrix(imm);
    std::cout << "\n";
}

void testSub()
{
    std::cout << "----- SUBTRACTION -----\n\n";
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M1 - 1:\n";
    printMatrix(im - 1);
    std::cout << "\n";

    std::cout << "M2 - 1.5:\n";
    printMatrix(im - 1.5);
    std::cout << "\n";

    std::cout << "M1 - M2:\n";
    printMatrix(im - dm);
    std::cout << "\n";

    std::cout << "M2 - M1:\n";
    printMatrix(dm - im);
    std::cout << "\n";

    Matrix<int> imm(im);
    std::cout << "M1 -= M2:\n";
    imm -= dm;
    printMatrix(imm);
    std::cout << "\n";

    Matrix<double> dmm(dm);
    std::cout << "M2 -= M1:\n";
    dmm -= im;
    printMatrix(dmm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 -= 1:\n";
    imm -= 1;
    printMatrix(imm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 -= 1.5:\n";
    imm -= 1.5;
    printMatrix(imm);
    std::cout << "\n";
}

void testMul()
{
    std::cout << "----- MULTIPLICATION -----\n\n";
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M1 * 2:\n";
    printMatrix(im * 2);
    std::cout << "\n";

    std::cout << "M2 * 1.5:\n";
    printMatrix(im * 1.5);
    std::cout << "\n";

    std::cout << "M1 * M2:\n";
    printMatrix(im * dm);
    std::cout << "\n";

    std::cout << "M2 * M1:\n";
    printMatrix(dm * im);
    std::cout << "\n";

    Matrix<int> imm(im);
    std::cout << "M1 *= M2:\n";
    imm *= dm;
    printMatrix(imm);
    std::cout << "\n";

    Matrix<double> dmm(dm);
    std::cout << "M2 *= M1:\n";
    dmm *= im;
    printMatrix(dmm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 *= 1:\n";
    imm *= 1;
    printMatrix(imm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 *= 1.5:\n";
    imm *= 1.5;
    printMatrix(imm);
    std::cout << "\n";
}

int main()
{
    testAdd();
    testSub();
    testMul();
    return 0;
}
