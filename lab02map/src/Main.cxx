#include "hashmap/HashMap.hpp"
#include <iostream>

int main()
{
    HashMap<std::string, int> hashmap;

    hashmap.insert("hello world", 1);
    hashmap.insert("meow", 2);
    hashmap.insert("nigga", 123);
    hashmap.insert("higger", 10);

    for (auto start = hashmap.begin(); start != hashmap.end(); ++start)
    {
        std::cout << start->key << " : " << start->value << std::endl;
        std::cout << "Found: " << (hashmap.find(start->key + "1") != hashmap.end()) << std::endl;
    }
    return 0;
}
