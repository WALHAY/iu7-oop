#include <bucket/Bucket.hpp>
#include <iostream>

int main()
{
	Bucket<int> bucket;

	bucket.insertTail(1);
	bucket.insertTail(2);
	bucket.insertTail(3);
	for(auto it = bucket.begin(); it != bucket.end(); ++it)
	{
		std::cout << "Value: " << *it << std::endl;
		// std::fflush(stdout);
	}

    return 0;
}
