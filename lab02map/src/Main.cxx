#include "hashmap/HashMap.hpp"
#include <iostream>
#include <string>

int main()
{
    HashMap<std::string, int> hashmap2(3);

    for (int i = 'a'; i < 'z'; ++i)
    {
        auto start = hashmap2.emplace(std::format("cat{}", char(i)), i);
    }

    for (auto start = hashmap2.begin(); start != hashmap2.end(); ++start)
    {
        std::cout << start->key << " : " << start->value << std::endl;
    }
    std::cout << "Found: " << (hashmap2.find("cata") != hashmap2.end()) << std::endl;


    return 0;
}
