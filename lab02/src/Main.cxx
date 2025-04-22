#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
	Matrix mx = { {1, 2}, {3, 4} };
	Matrix mx2 = { {-9, 8}, {5, 6} };

	auto res = mx + mx2;

	mx += mx;

	std::cout << "mx[1][1]: " << mx[1][1] << std::endl;

	for(const auto &it : mx)
		std::cout << it << " ";
    return 0;
}
