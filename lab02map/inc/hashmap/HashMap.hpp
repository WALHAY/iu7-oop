#pragma once

#include <bucket/BucketConcepts.hpp>

template<typename K, typename V>
	requires HashAndEqual<K>
class HashMap {

public:

private:
	float calculateLoadFactor();

	void resize(size_t newSize);

	std::hash<K> keyHash(K key);


};
