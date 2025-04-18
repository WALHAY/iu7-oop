#pragma once

#include "hashmap/HashMap.hpp"
#include <iostream>
#include <ostream>

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
HashMap<K, V, Hash>::HashMap() : HashMap(8)
{
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
HashMap<K, V, Hash>::HashMap(size_t size) : hasher(Hash())
{
    buckets = List<List<value_type>>(size);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
HashMap<K, V, Hash>::HashMap(const std::initializer_list<std::pair<K, V>> list) : HashMap(list.size())
{
    for (auto &pair : list)
        emplace(pair);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
bool HashMap<K, V, Hash>::contains(const K &key) const
{
    size_type bucket = getBucket(key);

    return false;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
bool HashMap<K, V, Hash>::contains(K &&key) const
{
    return contains(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::emplace(const K &key, const V &value) -> std::pair<iterator, bool>
{
    return emplace(std::make_pair(key, value));
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::emplace(value_type entry) -> std::pair<iterator, bool>
{
    if (countLoadFactor() > maxLoadFactor)
        rebuild();

    return insert(buckets, entry);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::find(const K &key) -> iterator
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });

    return iterator(buckets.begin() + index, buckets.end(), it);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::find(const K &key) const -> const_iterator
{
    return find(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
bool HashMap<K, V, Hash>::erase(const K &key)
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });
    if (it == end(index))
        return false;

    buckets[index].erase(it);

    return true;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
void HashMap<K, V, Hash>::clear()
{
    for (auto &bucket : buckets)
        bucket.clear();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
V &HashMap<K, V, Hash>::at(const K &key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __PRETTY_FUNCTION__, __LINE__);

    return it->second;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
const V &HashMap<K, V, Hash>::at(const K &key) const
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
V &HashMap<K, V, Hash>::operator[](const K &key)
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
V &HashMap<K, V, Hash>::operator[](K &&key)
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::begin() -> iterator
{
    return iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::end() -> iterator
{
    return iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::begin() const -> const_iterator
{
    return const_iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::end() const -> const_iterator
{
    return const_iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::cbegin() const -> const_iterator
{
    return const_iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::cend() const -> const_iterator
{
    return const_iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::begin(size_type bucket) -> local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::end(size_type bucket) -> local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::getBucket(const K &key) const -> size_type
{
    return getKeyHash(key) % getBucketCount();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
size_t HashMap<K, V, Hash>::getKeyHash(const K &key) const
{
    return hasher(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
float HashMap<K, V, Hash>::countLoadFactor() const
{
    return static_cast<float>(getSize()) / getBucketCount();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
void HashMap<K, V, Hash>::rebuild()
{
    size_type nextSize = getNextPrime(static_cast<size_type>(getSize() * sizeFactor));

    List<List<value_type>> nextBuckets(nextSize);
    for (auto i = buckets.begin(); i != buckets.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
        {
            insert(nextBuckets, *j);
        }
    }

    buckets = nextBuckets;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::insert(List<List<value_type>> &buckets, value_type &entry) -> std::pair<iterator, bool>
{
    size_t hash = getKeyHash(entry.first);
    size_type index = hash % buckets.getSize();
    auto &bucket = buckets[index];

    ListIterator<value_type> res = bucket.pushFront(entry);
    return std::make_pair(iterator(buckets.begin() + index, buckets.end(), res), true);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::getNextPrime(size_type size) const -> size_type
{
    while (size < std::numeric_limits<size_type>::max() && !isPrime(++size))
        ;
    return size;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
bool HashMap<K, V, Hash>::isPrime(size_type value) const
{
    for (size_type i = 2; i < value; ++i)
        if (value % i == 0)
            return false;
    return true;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::getBucketCount() const -> size_type
{
    return buckets.getSize();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash>
auto HashMap<K, V, Hash>::getSize() const -> size_type
{
    size_type size = 0;
    for (auto &bucket : buckets)
        size += bucket.getSize();
    return size;
}
