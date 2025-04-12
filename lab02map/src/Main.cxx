#include "bucket/Bucket.hpp"
#include "bucket/BucketNode.hpp"
#include <iostream>

int main() {
	Bucket<std::string, int> bucket;

	bucket.insert("123", 111);
	std::cout << bucket.find("123").value();
	return 0;
}
