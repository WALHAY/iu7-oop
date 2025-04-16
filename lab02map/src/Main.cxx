#include "hashmap/HashMap.hpp"
#include <bucket/Bucket.hpp>
#include <iostream>

int main()
{
    HashMap<std::string, int> hashmap(4);

	hashmap.emplace("Nigga1", 1);
	hashmap.emplace("Nigga2", 2);
	hashmap.emplace("Nigga3", 3);
	hashmap.emplace("Nigga4", 4);
	auto it = hashmap.begin();
    for (; it != hashmap.end(); ++it)
    {
        std::cout << "Value: " << it->first << " : " << it->second << std::endl;
    }

    return 0;
}
