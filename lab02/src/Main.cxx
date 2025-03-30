#include "../inc/Matrix.hpp"

int main() {
	Matrix<int> mx = {{1, 2, 3}, {4, 5, 6}};
	mx.resize(5, 5);
	mx.print();
	return 0;
}
