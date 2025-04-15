#pragma once

#include "bucket/Bucket.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, MoveAndCopy V>
class HashMap;

template <typename K, typename V>
class HashMapIterator
{
  public:
    using iterator = HashMapIterator<K, V>;

    HashMapIterator();
    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const HashMapIterator<K, V> &map);
    HashMapIterator(const std::shared_ptr<Bucket<typename HashMap<K, V>::value_type>[]> &buckets);

  protected:
};

#include <hashmap/iterators/HashMapIterImpl.hpp>
