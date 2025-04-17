#pragma once

#include "hashmap/iterators/ConstHashMapIter.hpp"

template <typename K, typename V>
ConstHashMapIterator<K, V>::ConstHashMapIterator()
{
}

template <typename K, typename V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const buckets_iterator &current, const buckets_iterator &end)
    : ConstHashMapIterator(current, end, current != end ? current->begin() : local_iterator(nullptr))
{
}

template <typename K, typename V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const buckets_iterator &current, const buckets_iterator &end,
                                       const local_iterator &element)
{
    this->currentBucket = current;
    this->endBucket = end;
    this->elementIterator = element;
}

template <typename K, typename V>
auto ConstHashMapIterator<K, V>::operator->() const -> const_pointer
{
    return &(elementIterator.getPtr()->getValueRef());
}

template <typename K, typename V>
auto ConstHashMapIterator<K, V>::operator*() const -> const_reference
{
    return elementIterator.getPtr()->getValueRef();
}

template <typename K, typename V>
ConstHashMapIterator<K, V>::operator bool() const
{
    return elementIterator;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator=(const ConstHashMapIterator<K, V> &other)
{
}

template <typename K, typename V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator++()
{
    ++elementIterator;
    moveNextBucket();
    return *this;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator++(int)
{
    iterator copy(*this);
    ++(*this);
    return copy;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator+(size_type offset) const
{
	ConstHashMapIterator<K, V> newIter(*this);
	return newIter + offset;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator+=(size_type offset)
{
	while(--offset > 0)
		++(*this);
	return *this;
}

template <typename K, typename V>
bool ConstHashMapIterator<K, V>::operator==(const ConstHashMapIterator<K, V> &iterator) const
{
    return currentBucket == iterator.currentBucket && endBucket == iterator.endBucket &&
           elementIterator == iterator.elementIterator;
}

template <typename K, typename V>
bool ConstHashMapIterator<K, V>::operator!=(const ConstHashMapIterator<K, V> &iterator) const
{
    return !(*this == iterator);
}

template <typename K, typename V>
void ConstHashMapIterator<K, V>::moveNextBucket()
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

static_assert(std::forward_iterator<ConstHashMapIterator<std::string, int>>);
