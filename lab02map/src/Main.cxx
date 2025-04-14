#include "hashmap/HashMap.hpp"
#include <iostream>
#include <string>

int main()
{
	HashMap<std::string, int> hashmap = { {"hello", 1}, {"hi", 2} };

	auto it = hashmap.cend();
	while(it != hashmap.cbegin())
	   {
		   --it;
	       std::cout << it->key << " : " << it->value << std::endl;
	   }


    return 0;
}
