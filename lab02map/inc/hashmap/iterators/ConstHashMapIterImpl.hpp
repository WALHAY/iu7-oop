#pragma once

#include "hashmap/iterators/ConstHashMapIter.hpp"

template <typename K, typename V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const buckets_iterator &current, const buckets_iterator &end)
    : ConstHashMapIterator(current, end, current != end ? current->begin() : local_iterator(nullptr))
{
    if (elementIterator == local_iterator(nullptr))
        moveNextBucket();
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
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator=(const ConstHashMapIterator<K, V> &other)
{
    this->elementIterator = other.elementIterator;
    this->currentBucket = other.currentBucket;
    this->endBucket = other.endBucket;
}

template <typename K, typename V>
auto ConstHashMapIterator<K, V>::operator->() const -> pointer
{
    validateIterator(__LINE__);
    return &(elementIterator.getPtr()->getValueRef());
}

template <typename K, typename V>
auto ConstHashMapIterator<K, V>::operator*() const -> reference
{
    validateIterator(__LINE__);
    return elementIterator.getPtr()->getValueRef();
}

template <typename K, typename V>
ConstHashMapIterator<K, V>::operator bool() const
{
    return isValid();
}

template <typename K, typename V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator++()
{
    validateIterator(__LINE__);
    if (elementIterator)
        ++elementIterator;
    moveNextBucket();
    return *this;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator++(int)
{
    validateIterator(__LINE__);
    iterator copy(*this);
    ++(*this);
    return copy;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator+(size_type offset) const
{
    validateIterator(__LINE__);
    ConstHashMapIterator<K, V> newIter(*this);
    return newIter + offset;
}

template <typename K, typename V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator+=(size_type offset)
{
    validateIterator(__LINE__);
    while (--offset > 0)
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
bool ConstHashMapIterator<K, V>::isValid() const
{
    return currentBucket.isValid() && elementIterator.isValid();
}

template <typename K, typename V>
void ConstHashMapIterator<K, V>::validateIterator(int line) const
{
    if (!isValid())
        throw InvalidIterator(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, line);
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
