#include "hashmap/HashMap.hpp"
#include <iostream>

int main()
{
    HashMap<std::string, int> hashmap2(3);

	for(int i = 'a'; i < 'z'; ++i)
	{
    	hashmap2.insert(std::format("cat{}", char(i)), i);
		std::cout << "Buckets: " << hashmap2.getBucketCount() << " Size: " <<hashmap2.getSize() << std::endl;
	}

    for (auto start = hashmap2.begin(); start != hashmap2.end(); ++start)
    {
        std::cout << start->key << " : " << start->value << std::endl;
        // std::cout << "Found: " << (hashmap.find(start->key + "1") != hashmap.end()) << std::endl;
    }

    return 0;
}
