#pragma once

#include "hashmap/iterators/HashMapIter.hpp"

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator()
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMap<K, V> &map) : HashMapIterator(map, 0)
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMap<K, V> &map, size_type bucket)
{
    bucketIndex = bucket;
    bucketCount = map.bucketCount;
    bucketsPtr = map.buckets;
}

// template <typename K, typename V>
// auto HashMapIterator<K, V>::operator->() -> pointer
// {
//     return localIterator.getPtr()->getValueRef();
// }
//
// template <typename K, typename V>
// auto HashMapIterator<K, V>::operator->() const -> const_pointer
// {
//     return localIterator.getPtr()->getValueRef();
// }
//
// template <typename K, typename V>
// auto HashMapIterator<K, V>::operator*() -> reference
// {
//     return localIterator.getPtr()->getValueRef();
// }
// template <typename K, typename V>
// auto HashMapIterator<K, V>::operator*() const -> const_reference
// {
//     return localIterator.getPtr()->getValueRef();
// }

template <typename K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator++()
{
    if (++localIterator == bucketsPtr.lock()[bucketIndex].end())
    {
        size_type next = findNextBucket();
        localIterator = bucketsPtr.lock()[next].begin();
    }

    return *this;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator==(const HashMapIterator<K, V> &iterator) const {
	return localIterator == iterator.localIterator;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator!=(const HashMapIterator<K, V> &iterator) const {
	return localIterator != iterator.localIterator;
}

template <typename K, typename V>
auto HashMapIterator<K, V>::findNextBucket() -> size_type
{
    size_type next = bucketIndex;
    while (true)
    {
        next++;
        auto &bucket = bucketsPtr.lock()[next];

        if (bucket.end() != bucket.begin())
            return bucketIndex;
    }
}
