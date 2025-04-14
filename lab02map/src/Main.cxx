#include "hashmap/HashMap.hpp"
#include <iostream>
#include <string>

int main()
{
    HashMap<std::string, int> hashmap2(3);

    for (int i = 0; i < 1230; ++i)
    {
        auto start = hashmap2.emplace(std::format("cat{}", i), i);
    }

	//    for (auto start = hashmap2.begin(); start != hashmap2.end(); ++start)
	//    {
	//        std::cout << start->key << " : " << start->value << std::endl;
	//    }
	// hashmap2.clear();
	//    std::cout << "Found: " << (hashmap2.contains("cata")) << std::endl;


    return 0;
}
