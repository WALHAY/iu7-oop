#include "matrix/Matrix.hpp"
#include <cctype>
#include <iostream>
#include <vector>

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
    Matrix<double> dm = {{-0.6, 0.5}, {0.3, -0.7}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "~M1:\n";
    printMatrix(~im);
    std::cout << "\n";

    std::cout << "~M1 * M1:\n";
    printMatrix(~im * im);
    std::cout << "Is identity: " << (~im * im).isIdentity() << "\n";
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(dm);
    std::cout << "\n";

    std::cout << "M2:\n";
    printMatrix(~dm);
    std::cout << "\n";

    std::cout << "~M2 * M2:\n";
    printMatrix(~dm * dm);
    std::cout << "Is identity: " << (~dm * dm).isIdentity() << "\n";
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

void testManagement()
{
    printTitle("management");
    Matrix<int> im = {{1, 2}, {3, 4}};

    std::cout << "M1:\n";
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Insert row at 1\n";
    im.insertRow(1);
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Insert column at 2\n";
    im.insertColumn(2);
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Insert row of {7, 8, 9} at 3\n";
    im.insertRow(3, std::vector{7, 8, 9});
    printMatrix(im);
    std::cout << "\n";

    std::cout << "Insert column of {5, 6, 9, 9} at 1\n";
    im.insertColumn(1, std::vector{5, 6, 9, 9});
    printMatrix(im);
    std::cout << "\n";

    Matrix<int> imm(im);
    std::cout << "Remove row 0\n";
    imm.removeRow(0);
    printMatrix(imm);
    std::cout << "\n";

    imm = Matrix<int>(im);
    std::cout << "Remove column 0\n";
    imm.removeColumn(0);
    printMatrix(imm);
    std::cout << "\n";
    return;

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

void testIterators()
{
    printTitle("iterators");
    Matrix<int> im = {{1, 2}, {3, 4}};

    std::cout << "Reverse\n";
    for (auto it = im.crbegin(); it != im.crend(); ++it)
    {
        std::cout << *it << " ";
    }
	std::cout << "\n\n";
}

void testDefaultMatrices()
{
    printTitle("default matrices");

    std::cout << "Zero int matrix(3, 2):\n";
    printMatrix(Matrix<int>::zero(3, 2));
	std::cout << "\n";

    std::cout << "Fill(6.66) matrix(3, 4):\n";
    printMatrix(Matrix<double>::fill(3, 4, 6.66));
	std::cout << "\n";

    std::cout << "Identity int matrix(5):\n";
    printMatrix(Matrix<int>::identity(5));
	std::cout << "\n";

    std::cout << "Diagonal char matrix(4, 'a'):\n";
    printMatrix(Matrix<char>::diagonal(4, 'a'));
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
    testManagement();
    testHadamard();
    testIterators();
    testDefaultMatrices();
    return 0;
}
