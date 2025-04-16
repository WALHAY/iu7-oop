#pragma once

#include "hashmap/iterators/HashMapIter.hpp"
#include <iostream>

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator()
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMap<K, V> &map) : HashMapIterator(map.begin(), map.end())
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const buckets_iterator &current, const buckets_iterator &end)
    : HashMapIterator(current, end, current != end ? current->begin() : local_iterator(nullptr))
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const buckets_iterator &current, const buckets_iterator &end,
                                       const local_iterator &element)
{
    this->currentBucket = current;
    this->endBucket = end;
    this->elementIterator = element;
}

template <typename K, typename V>
auto HashMapIterator<K, V>::operator->() const -> pointer
{
    return &(elementIterator.nodePtr.lock().get()->getValueRef());
}

template <typename K, typename V>
auto HashMapIterator<K, V>::operator*() const -> reference
{
    return elementIterator.nodePtr.lock().get()->getValueRef();
}

template <typename K, typename V>
HashMapIterator<K, V>::operator bool() const
{
    return elementIterator;
}

template <typename K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator=(const HashMapIterator<K, V> &other)
{
}

template <typename K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator++()
{
	++elementIterator;
	moveNextBucket();
    return *this;
}

template <typename K, typename V>
HashMapIterator<K, V> HashMapIterator<K, V>::operator++(int)
{
    iterator copy(*this);
    ++(*this);
    return copy;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator==(const HashMapIterator<K, V> &iterator) const
{
    return currentBucket == iterator.currentBucket && endBucket == iterator.endBucket && elementIterator == iterator.elementIterator;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator!=(const HashMapIterator<K, V> &iterator) const
{
    return !(*this == iterator);
}

template <typename K, typename V>
void HashMapIterator<K, V>::moveNextBucket()
{
    while (currentBucket != endBucket && elementIterator == currentBucket->end())
    {
        ++currentBucket;
        if (currentBucket != endBucket)
        {
            elementIterator = currentBucket->begin();
        }
    }
}

static_assert(std::forward_iterator<HashMapIterator<std::string, int>>);
