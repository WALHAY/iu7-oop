#include "hashmap/HashMap.hpp"
#include <bucket/Bucket.hpp>
#include <iostream>

int main()
{
	HashMap<std::string, int> hashmap;

	hashmap.emplace("Nigga", 1);
	// std::cout << "Found: " << (hashmap.find("Nigga") != hashmap.end()) << std::endl;

    return 0;
}
