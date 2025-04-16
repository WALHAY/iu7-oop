#pragma once

#include "hashmap/iterators/HashMapIter.hpp"

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
    : HashMapIterator(current, end, current->begin())
{
}

template <typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(const buckets_iterator &current, const buckets_iterator &end, const local_iterator &element)
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
	if(++elementIterator == currentBucket->end())
	{
		++currentBucket;
	} 
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
    return true;
}

template <typename K, typename V>
bool HashMapIterator<K, V>::operator!=(const HashMapIterator<K, V> &iterator) const
{
    return !(*this == iterator);
}

static_assert(std::forward_iterator<HashMapIterator<std::string, int>>);
