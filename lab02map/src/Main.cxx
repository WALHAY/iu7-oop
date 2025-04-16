#include "hashmap/HashMap.hpp"
#include <list/List.hpp>
#include <iostream>

int main()
{
	std::cout << "\n--- Linked list zone ---" << std::endl;
	List<std::string> strList;
	std::cout << "Is empty: " << strList.isEmpty() << std::endl;
	std::cout << "List insert head \"hello\"" << std::endl;
	strList.insertHead("hello");
	std::cout << "list.[0]: " << strList[0] << std::endl;
	std::cout << "list.at(0): " << strList.at(0) << std::endl;

	std::cout << "\nAdded cat and meow into list head" << std::endl;
	strList.insertHead("cat");
	strList.insertHead("meow");

	std::cout << "List size: " << strList.getSize() << std::endl;
	std::cout << "Is empty: " << strList.isEmpty() << std::endl;
	std::cout << "Iterating head -> tail: ";
	for(auto &it : strList)
		std::cout << it << " ";
	std::cout << "\n";

	std::cout << "\nAdded dog and brr into list tail" << std::endl;
	strList.insertTail("dog");
	strList.insertTail("brr");

	std::cout << "List size: " << strList.getSize() << std::endl;
	std::cout << "Is empty: " << strList.isEmpty() << std::endl;
	std::cout << "Iterating head -> tail: ";
	for(auto &it : strList)
		std::cout << it << " ";
	std::cout << "\n";

	std::cout << "\n--- HashMap zone ---" << std::endl;

	// HashMap<std::string, int> hashmap;
	//
	// hashmap.emplace("hello", 1);
	// std::cout << "Hashmap emplace {\"hello\", 1}" << std::endl;
	// std::cout << "hashmap[\"hello\"]: " << hashmap["hello"] << std::endl;
	// std::cout << "hashmap[\"hello\"]: " << hashmap.at("hello") << std::endl;

    return 0;
}
