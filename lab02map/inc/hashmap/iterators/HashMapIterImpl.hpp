#pragma once

#include "hashmap/iterators/HashMapIter.hpp"

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator()
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMap<K, V> &map)
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMapIterator<K, V> &map)
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const std::shared_ptr<Bucket<typename HashMap<K, V>::value_type>[]> &buckets)
{
}
