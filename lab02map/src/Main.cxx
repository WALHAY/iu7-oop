#include "hashmap/HashMap.hpp"
#include <iostream>
#include <list/List.hpp>

int main()
{
    std::cout << "\n--- Linked list zone ---" << std::endl;
    List<std::string> strList;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List insert head \"hello\"" << std::endl;
    strList.pushFront("hello");
    std::cout << "list.[0]: " << strList[0] << std::endl;
    std::cout << "list.at(0): " << strList.at(0) << std::endl;

    std::cout << "\nInsert head: cat & meow" << std::endl;
    strList.pushFront("cat");
    strList.pushFront("meow");

    std::cout << "List size: " << strList.getSize() << std::endl;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nHead: " << strList.getFront() << std::endl;
    std::cout << "Tail: " << strList.getBack() << std::endl;

    std::cout << "\nInsert tail: dog & brr" << std::endl;
    strList.pushBack("dog");
    strList.pushBack("brr");

    std::cout << "List size: " << strList.getSize() << std::endl;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nHead: " << strList.getFront() << std::endl;
    std::cout << "Tail: " << strList.getBack() << std::endl;
    std::cout << "\n";

    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nRemove head" << std::endl;
    strList.popFront();
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nList size: " << strList.getSize() << std::endl;
    std::cout << "Head: " << strList.getFront() << std::endl;
    std::cout << "Tail: " << strList.getBack() << "\n\n";

    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nRemove tail" << std::endl;
    strList.popBack();
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nList size: " << strList.getSize() << std::endl;
    std::cout << "Head: " << strList.getFront() << std::endl;
    std::cout << "Tail: " << strList.getBack() << std::endl;

    List<std::string> copyList(strList);
    std::cout << "\nCopied list: ";
    for (auto &it : copyList)
        std::cout << it << " ";

    List<std::string> copyList2;
    copyList2 = copyList;
    std::cout << "\nCopied list 2: ";
    for (auto &it : copyList2)
        std::cout << it << " ";

    List<std::string> initList = {"This", "initialized", "by", "list"};
    std::cout << "\nList initializer: ";
    for (auto &it : initList)
        std::cout << it << " ";

    std::cout << "\n\n2-Dim List:" << std::endl;
    List<List<std::string>> doubleList;
    doubleList.pushFront(strList);
    doubleList.pushFront(initList);

    for (auto &list : doubleList)
    {
        for (auto &str : list)
        {
            std::cout << str << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n--- HashMap zone ---" << std::endl;

    HashMap<std::string, int> hashmap;

    hashmap.insert("hello", 1);
    hashmap.insert("hi", 25);
    hashmap.insert("meow", 100);
    hashmap.insert("cat", 123);
    std::cout << "\nHashmap size: " << hashmap.getSize() << std::endl;

    for (auto &it : hashmap)
    {
        std::cout << it.first << " : " << it.second << std::endl;
    }

    std::cout << "Removed: " << hashmap.erase("meow") << std::endl;

    std::cout << "hashmap[\"hello\"]: " << hashmap["hello"] << std::endl;
    std::cout << "hashmap.at(\"hi\"): " << hashmap.at("hi") << std::endl;

    HashMap<std::string, int> bucketCheck;
    size_t buckets = bucketCheck.getBucketCount();
    for (int i = 0; i < 100; ++i)
    {
        bucketCheck.insert(std::format("Check{}", i), i);
        if (buckets != bucketCheck.getBucketCount())
        {
            buckets = bucketCheck.getBucketCount();
            std::cout << "New bucket count: " << buckets << std::endl;
        }
    }

    List<std::pair<int, int>> pairList = {{1, 1}, {2, 3}, {5, 10}};

    HashMap<int, int> pairMap(pairList.begin(), pairList.end());

    for (auto it = hashmap.cbegin(); it != hashmap.cend(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

    return 0;
}
