#include "hashmap/HashMap.hpp"
#include <list/List.hpp>
#include <iostream>

int main()
{
    HashMap<std::string, int> hashmap(10);

    for (int i = 0; i < 10; ++i)
    {
        auto res = hashmap.emplace(std::format("Nigga{}", i), i);
        std::cout << "Has been added: " << res.second << "\n";
    }

    for (auto &it : hashmap)
    {
        // std::cout << "Value: " << it.first << " : " << it.second << std::endl;
        std::fflush(stdout);
    }

    //  for (int i = 0; i < hashmap.bucketCount; ++i)
    //  {
    // std::cout << "Bucket: " << i << std::endl;
    //      for (auto &it : hashmap.buckets[i])
    //          std::cout << "\t" << it.first << std::endl;
    //  }

    return 0;
}
