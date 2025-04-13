#include "hashmap/HashMap.hpp"
#include <iostream>

int main()
{
    HashMap<std::string, int> hashmap;

    hashmap.insert("hello world", 1);
    hashmap.insert("meow", 2);
    hashmap.insert("nigga", 123);
    hashmap.insert("higger", 10);

    HashMap<std::string, int> hashmap2(hashmap);

    for (auto start = hashmap2.begin(); start != hashmap2.end(); ++start)
    {
        std::cout << start->key << " : " << start->value << std::endl;
        // std::cout << "Found: " << (hashmap.find(start->key + "1") != hashmap.end()) << std::endl;
    }

    return 0;
}
