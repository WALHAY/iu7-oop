#include "matrix/Matrix.hpp"
#include <iostream>

int main()
{
	Matrix mx = { {1, 2}, {3, 4} };

	for(auto it = mx.begin(); it != mx.end(); ++it)
		std::cout << *it << " ";
    return 0;
}
