#include "hashmap/HashMap.hpp"
#include <iostream>
#include <list/List.hpp>

template <typename T>
void printList(const List<T> &list)
{
    std::cout << "list: ";
    for (auto &it : list)
        std::cout << it << " ";
    std::cout << std::endl;
}

void checkList()
{
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
    auto it = std::find(list.begin(), list.end(), 3);
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

template <typename K, typename V>
void printMap(const HashMap<K, V> &map)
{
    std::cout << "map: ";
    for (auto &it : map)
        std::cout << "{" << it.first << ":" << it.second << "} ";
    std::cout << std::endl;
}

void checkMap()
{
	auto hashmap = HashMap<std::string, int>();
	std::cout << "map = HashMap<>()\n";
	printMap(hashmap);

	std::cout << "insert('hi', 123)\n";
	std::cout << "insert('hello', 10)\n";
	std::cout << "insert(std::make_pair('cat', 1))\n";
	hashmap.insert("hi", 123);
	hashmap.insert("hello", 10);
	hashmap.insert(std::make_pair("cat", 1));
	printMap(hashmap);

	std::cout << "insert_or_assign('cat', 999)\n";
	std::cout << "insert_or_assign(std::make_pair('foo', 101))\n";
	hashmap.insert_or_assign("cat", 999);
	hashmap.insert_or_assign(std::make_pair("foo", 101));
	printMap(hashmap);

	std::cout << "hashmap['cat'] = " << hashmap["cat"] << std::endl;
	std::cout << "hashmap.at('hi') = " << hashmap.at("hi") << std::endl;
	auto it = hashmap.find("cat");
	std::cout << "find('cat') = {" << it->first << ":" << it->second << "}" << std::endl;
	std::cout << "contains('hello') = " << hashmap.contains("i") << std::endl;

	std::cout << "erase('hi') = " << hashmap.erase("hello") << std::endl;
	printMap(hashmap);

	std::cout << "getBucketCount() = " << hashmap.getBucketCount() << std::endl;
	std::cout << "getSize() = " << hashmap.getSize() << std::endl;

	std::cout << "clear()\n";
	hashmap.clear();
	printMap(hashmap);
}

int main()
{
	std::cout << "--- CHECK LIST ---\n\n";
    // checkList();
	std::cout << "\n--- CHECK MAP ---\n"; 
	checkMap();
}
