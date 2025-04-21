#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
	Matrix mx = { {1, 2}, {3, 4} };

	for(const auto &it : (mx + 1))
		std::cout << it << " ";
    return 0;
}
