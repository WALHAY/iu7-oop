#include "hashmap/HashMap.hpp"
#include <iostream>
#include <list/List.hpp>

template<typename T>
void printList(const List<T>& list)
{
	std::cout << "list: ";
	for(auto &it : list)
		std::cout << it << " ";
	std::cout << "" << std::endl;
}

void checkList() {
	List<int> list;
	printList(list);
	std::cout << "pushBack(10)\n";
	list.pushBack(10);
	printList(list);
	std::cout << "pushFront(5)\n";
	list.pushFront(5);
	printList(list);
	std::cout << "front: " << list.getFront() << std::endl;
	std::cout << "back: " << list.getBack() << std::endl;
	std::cout << "size: " << list.getSize() << std::endl;

	std::cout << "popFront()\n";
	list.popFront();
	printList(list);

	std::cout << "popBack()\n";
	list.popBack();
	printList(list);

	std::cout << "resize(3)\n";
	list.resize(3);
	printList(list);

	std::cout << "resize(10, 7)\n";
	list.resize(10, 7);
	printList(list);

	std::cout << "list := {1, 2, 3, 4, 5}\n";
	list = {1, 2, 3, 4, 5};
	printList(list);

	std::cout << "it = std::find(begin, end, 3)\n";
	auto it = std:: find(list.begin(), list.end(), 3);
	std::cout << "found: " << it << std::endl;

	std::cout << "erase(it)\n";
	list.erase(it);
	printList(list);

	std::cout << "list[3] = " << list[3] << std::endl;
	std::cout << "list.at(2) = " << list.at(2) << std::endl;

	std::cout << "clear()\n";
	list.clear();
	printList(list);

	std::cout << "list = List<>(5, 5)\n";
	list = List<int>(5, 5);
	printList(list);

	std::cout << "list = List<>(5)\n";
	list = List<int>(5);
	printList(list);
}

int main()
{
	checkList();
}
