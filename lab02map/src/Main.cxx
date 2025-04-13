#include "hashmap/HashMap.hpp"
#include <iostream>
#include <string>
int main() {
	HashMap<std::string, int> hashmap(8);

	hashmap.insert("hello world", 1);
	std::optional<int> value = hashmap.find("hello world");
	if(value.has_value())
		std::cout << "contains: " << value.value();
	else 
		std::cout << "not contains";
	return 0;
}
