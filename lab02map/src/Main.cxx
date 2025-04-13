#include "hashmap/HashMap.hpp"
#include <iostream>
int main() {
	HashMap<std::string, int> hashmap(8);

	hashmap.insert("hello world", 1);
	hashmap.insert("meow", 2);
	hashmap.insert("nigga", 123);
	hashmap.insert("higger", 10);
	for(auto start = hashmap.end(); start != hashmap.begin(); --start)
		std::cout << start->key << " " << start->value << std::endl;

	return 0;
}
