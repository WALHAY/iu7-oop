#include "hashmap/HashMap.hpp"
#include <iostream>
#include <string>

int main()
{
    HashMap<std::string, int> hashmap2(3);

    for (int i = 'a'; i < 'z'; ++i)
    {
        hashmap2.emplace(std::format("cat{}", char(i)), i);
    }

    for (auto start = hashmap2.begin(); start != hashmap2.end(); ++start)
    {
        std::cout << start->key << " : " << start->value << std::endl;
        // std::cout << "Found: " << (hashmap.find(start->key + "1") != hashmap.end()) << std::endl;
    }

    try
    {
        hashmap2["cat0"];
    }
    catch (BaseException e)
    {
        std::cout << e.what();
    }

    return 0;
}
