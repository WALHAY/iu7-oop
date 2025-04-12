#include "bucket/Bucket.hpp"
#include <iostream>

int main() {
	Bucket<std::string, int> bucket;

	bucket.insert("123", 111);
	bucket.insert("321", 555);
	bucket.insert("111", 666);
	bucket.remove("321");
	std::cout << bucket.contains("111");
	return 0;
}
