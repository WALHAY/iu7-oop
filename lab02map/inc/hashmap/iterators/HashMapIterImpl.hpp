#pragma once

#include "hashmap/iterators/HashMapIter.hpp"
#include <iostream>

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
    if (bucket >= bucketCount)
        localIterator = map.buckets[bucket].end();
    else
        localIterator = map.buckets[bucket].begin();
}

template <typename K, typename V>
auto HashMapIterator<K, V>::operator->() const -> pointer
{
    return &(localIterator.nodePtr.lock().get()->getValueRef());
}

template <typename K, typename V>
auto HashMapIterator<K, V>::operator*() const -> reference
{
    return localIterator.nodePtr.lock().get()->getValueRef();
}

template <typename K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator=(const HashMapIterator<K, V> &other)
{
    this->localIterator = other->localIterator;
    this->bucketCount = other->bucketCount;
    this->bucketsPtr = other->bucketsPtr;
    this->bucketIndex = other->bucketIndex;
}

template <typename K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator++()
{
    local_iterator bucketEnd = bucketsPtr.lock()[bucketIndex].end();
    if (++localIterator == bucketEnd)
    {
        while (bucketIndex + 1 < bucketCount)
        {
            auto &bucket = bucketsPtr.lock()[++bucketIndex];
            if (!bucket.isEmpty())
				break;
        }

		if(bucketIndex >= bucketCount)
			throw new InvalidIterator("", "", "", 1);

		localIterator = bucketsPtr.lock()[bucketIndex].begin();
    }

    return *this;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator==(const HashMapIterator<K, V> &iterator) const
{
    return localIterator == iterator.localIterator;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator!=(const HashMapIterator<K, V> &iterator) const
{
    return localIterator != iterator.localIterator;
}

static_assert(std::forward_iterator<HashMapIterator<std::string, int>>);
