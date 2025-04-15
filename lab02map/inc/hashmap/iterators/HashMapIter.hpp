#pragma once

#include "bucket/Bucket.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, MoveAndCopy V>
class HashMap;

template <typename K, typename V>
class HashMapIterator
{
  public:
	using size_type = std::size_t;
	using value_type = HashMap<K, V>::value_type;
    using iterator = HashMapIterator<K, V>;

    HashMapIterator();
    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const HashMapIterator<K, V> &map);
    HashMapIterator(const std::shared_ptr<Bucket<value_type>[]> &buckets);

  protected:
	std::weak_ptr<Bucket<value_type>[]> bucketPtr;

	size_type bucketIndex;
	BucketIterator<value_type> localIterator;
};

#include <hashmap/iterators/HashMapIterImpl.hpp>
