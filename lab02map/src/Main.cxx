#include "hashmap/HashMap.hpp"
#include <iostream>

int main() {
	HashMap<std::string, int> hashmap;
	hashmap.insert("hello", 123);
	std::cout << hashmap.contains("hello2");
	return 0;
}
