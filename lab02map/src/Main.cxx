#include "hashmap/HashMap.hpp"
#include <bucket/Bucket.hpp>
#include <iostream>

int main()
{
	HashMap<std::string, int> hashmap(1);

	std::cout << "Contains: " << " " << hashmap.contains("Nigga") << std::endl;
	auto res = hashmap.emplace("Nigga", 1);
	std::cout << "Result: " << " " << res.second << std::endl;
	auto res2 = hashmap.emplace("Nigga", 1);
	std::cout << "Result: " << " " << res2.second << std::endl;
	auto it = hashmap.begin(0);
	std::cout << "Contains: " << " " << hashmap.contains("Nigga") << std::endl;
	for(; it != hashmap.end(0); ++it)
	{
		std::cout << "Value: " << it->first << std::endl;
	}

    return 0;
}
