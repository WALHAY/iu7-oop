#include "matrix/Matrix.hpp"
#include <cctype>
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

void printTitle(std::string title)
{
    std::ranges::transform(title, title.begin(), [](const auto &c) { return std::toupper(c); });
    std::cout << std::format("----- {} -----\n\n", title);
}

void testAdd()
{
    printTitle("addition");
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
    printTitle("subtraction");
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
    printTitle("multiplication");
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

void testDiv()
{
    printTitle("division");
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M1 / 2:\n";
    printMatrix(im / 2);
    std::cout << "\n";

    std::cout << "M2 / 1.5:\n";
    printMatrix(im / 1.5);
    std::cout << "\n";

    std::cout << "M1 / M2:\n";
    printMatrix(im / dm);
    std::cout << "\n";

    std::cout << "M2 / M1:\n";
    printMatrix(dm / im);
    std::cout << "\n";

    Matrix<int> imm(im);
    std::cout << "M1 /= M2:\n";
    imm /= dm;
    printMatrix(imm);
    std::cout << "\n";

    Matrix<double> dmm(dm);
    std::cout << "M2 /= M1:\n";
    dmm /= im;
    printMatrix(dmm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 /= 2:\n";
    imm /= 2;
    printMatrix(imm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "M1 /= 1.5:\n";
    imm /= 1.5;
    printMatrix(imm);
    std::cout << "\n";

    std::cout << "M1 * M2 / M2\n";
    printMatrix(im * dm / dm);
    std::cout << "\n";

    std::cout << "M1 / M2 * M2\n";
    printMatrix(im / dm * dm);
    std::cout << "\n";

    std::cout << "M2 * M1 / M1\n";
    printMatrix(dm * im / im);
    std::cout << "\n";

    std::cout << "M2 / M1 * M1\n";
    printMatrix(dm / im * im);
    std::cout << "\n";
}

void testTranspose()
{
    printTitle("transpose");
    Matrix<int> im = {{1, 2, 6}, {3, 4, 4}};
    Matrix<double> dm = {{-0.6, 0.4, -0.2}, {0.3, -0.7, 1.1}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M1^T:\n";
    printMatrix(im.transpose());
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M2^T:\n";
    printMatrix(dm.transpose());
    std::cout << "\n";
}

void testInvert()
{
    printTitle("invert");
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "~M1:\n";
    printMatrix(~im);
    std::cout << "\n";

    std::cout << "~M1 * M1:\n";
    printMatrix(~im * im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(~dm);
    std::cout << "\n";

    std::cout << "~M2 * M2:\n";
    printMatrix(~dm * dm);
    std::cout << "\n";
}

void testDet()
{
    printTitle("determinant");
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};
    Matrix<int> imm = {{1, 3}, {2, 6}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "|M1|: " << im.det() << "\n\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "|M2|: " << dm.det() << "\n\n";

    std::cout << "M3:\n";
    printMatrix(imm);
    std::cout << "\n";

    std::cout << "|M3|: " << imm.det() << "\n\n";
}

void testSwap()
{
    printTitle("swap");
    Matrix<int> im = {{1, 2}, {3, 4}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Swap rows\n";
    im.swapRows(0, 1);
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Swap columns\n";
    im.swapColumns(0, 1);
    printMatrix(im);
}

void testHadamard()
{
    printTitle("hadamard");
    Matrix<int> im = {{1, 2}, {3, 4}};
    Matrix<double> dm = {{-0.6, 0.4}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "Hadamard M1 * M2:\n";
    printMatrix(im.hadamardMul(dm));
    std::cout << "\n";

    Matrix<double> dmm(dm);
    std::cout << "Hadamard M2 *= M1:\n";
    printMatrix(dm.hadamardMulAssign(im));
    std::cout << "\n";

    std::cout << "Hadamard M1 / M2:\n";
    printMatrix(im.hadamardDiv(dmm));
    std::cout << "\n";

    std::cout << "Hadamard M2 /= M1:\n";
    printMatrix(dmm.hadamardDivAssign(im));
    std::cout << "\n";
}

int main()
{
    testAdd();
    testSub();
    testMul();
    testDiv();
    testTranspose();
    testInvert();
    testDet();
    testSwap();
	testHadamard();
    return 0;
}
