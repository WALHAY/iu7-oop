#include "hashmap/HashMap.hpp"
#include <bucket/Bucket.hpp>
#include <iostream>

int main()
{
	HashMap<std::string, int> hashmap(1);

	auto res = hashmap.emplace("Nigga", 1);
	std::cout << "Result: " << " " << res.second << std::endl;
	auto it = hashmap.begin(0);
	for(; it != hashmap.end(0); ++it)
	{
		std::cout << "Value: " << it->first << std::endl;
	}

    return 0;
}
