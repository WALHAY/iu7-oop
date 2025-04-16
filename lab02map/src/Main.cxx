#include "hashmap/HashMap.hpp"
#include <iostream>
#include <list/List.hpp>

int main()
{
    std::cout << "\n--- Linked list zone ---" << std::endl;
    List<std::string> strList;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List insert head \"hello\"" << std::endl;
    strList.insertHead("hello");
    std::cout << "list.[0]: " << strList[0] << std::endl;
    std::cout << "list.at(0): " << strList.at(0) << std::endl;

    std::cout << "\nInsert head: cat & meow" << std::endl;
    strList.insertHead("cat");
    strList.insertHead("meow");

    std::cout << "List size: " << strList.getSize() << std::endl;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nHead: " << strList.getHead() << std::endl;
    std::cout << "Tail: " << strList.getTail() << std::endl;

    std::cout << "\nInsert tail: dog & brr" << std::endl;
    strList.insertTail("dog");
    strList.insertTail("brr");

    std::cout << "List size: " << strList.getSize() << std::endl;
    std::cout << "Is empty: " << strList.isEmpty() << std::endl;
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nHead: " << strList.getHead() << std::endl;
    std::cout << "Tail: " << strList.getTail() << std::endl;
    std::cout << "\n";

    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nRemove head" << std::endl;
    strList.removeHead();
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nList size: " << strList.getSize() << std::endl;
    std::cout << "Head: " << strList.getHead() << std::endl;
    std::cout << "Tail: " << strList.getTail() << "\n\n";

    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nRemove tail" << std::endl;
    strList.removeTail();
    std::cout << "List: ";
    for (auto &it : strList)
        std::cout << it << " ";
    std::cout << "\nList size: " << strList.getSize() << std::endl;
    std::cout << "Head: " << strList.getHead() << std::endl;
    std::cout << "Tail: " << strList.getTail() << std::endl;

	std::cout << "\n2-Dim List:" << std::endl;
    List<List<std::string>> doubleList;
    doubleList.insertHead(strList);
    doubleList.insertHead(strList);

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

    hashmap.emplace("hello", 1);
    hashmap.emplace("hi", 2);
    std::cout << "Hashmap emplace {\"hello\", 1}" << std::endl;

	for(auto &it : hashmap)
	{
		std::cout << it.first << " " <<it.second<<std::endl;
	}
    // std::cout << "hashmap[\"hello\"]: " << hashmap["hello"] << std::endl;
    // std::cout << "hashmap[\"hello\"]: " << hashmap.at("hello") << std::endl;

    return 0;
}
