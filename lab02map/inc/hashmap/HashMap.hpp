#pragma once

#include "bucket/Bucket.hpp"
#include "collection/BaseCollection.hpp"
#include <bucket/BucketConcepts.hpp>
#include <optional>

template<typename K, typename V>
	requires HashAndEqual<K>
class HashMap : public BaseCollection {

public:
	HashMap();
	explicit HashMap(const size_t initialSize);

	virtual ~HashMap() = default;

	void insert(const K& key, const V& value);

	std::optional<V> find(const K& key);

	bool contains(const K& key);

	void remove(const K& key);

private:
	size_t getEffectiveIndex(const K& key);

	void rebuild();

	size_t getNextPrime();

	float calculateLoadFactor();

	void resize(size_t newSize);

	size_t keyHash(const K& key);

	std::vector<Bucket<K, V>> buckets;
	float loadFactor;
	size_t bucketsCount;
};

#include <hashmap/HashMapImpl.hpp>
