#pragma once

#include "hashmap/HashMap.hpp"

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
HashMap<K, V, Hash, KeyFunction>::HashMap() : HashMap(8)
{
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
HashMap<K, V, Hash, KeyFunction>::HashMap(size_t size) : hashFunction(Hash()), keyEqualFunction(KeyFunction())
{
    buckets = List<List<value_type>>(size);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
HashMap<K, V, Hash, KeyFunction>::HashMap(std::initializer_list<value_type> list) : HashMap(list.begin(), list.end())
{
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
template <ConvertibleIterator<typename HashMap<K, V, Hash, KeyFunction>::value_type> Iter>
HashMap<K, V, Hash, KeyFunction>::HashMap(Iter &&begin, Iter &&end) : HashMap()
{
	for(Iter it = begin; it != end; ++it)
		emplace(*it);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
bool HashMap<K, V, Hash, KeyFunction>::contains(const K &key) const
{
    size_type bucket = getBucket(key);

    return false;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
bool HashMap<K, V, Hash, KeyFunction>::contains(K &&key) const
{
    return contains(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::emplace(const K &key, const V &value) -> std::pair<iterator, bool>
{
    return emplace(std::make_pair(key, value));
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::emplace(value_type entry) -> std::pair<iterator, bool>
{
    if (countLoadFactor() > maxLoadFactor)
        rebuild();

    return insert(buckets, entry);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::find(const K &key) -> iterator
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });

    return iterator(buckets.begin() + index, buckets.end(), it);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::find(const K &key) const -> const_iterator
{
    return find(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
bool HashMap<K, V, Hash, KeyFunction>::erase(const K &key)
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });
    if (it == end(index))
        return false;

    buckets[index].erase(it);

    return true;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
void HashMap<K, V, Hash, KeyFunction>::clear()
{
    for (auto &bucket : buckets)
        bucket.clear();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
V &HashMap<K, V, Hash, KeyFunction>::at(const K &key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __PRETTY_FUNCTION__, __LINE__);

    return it->second;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
const V &HashMap<K, V, Hash, KeyFunction>::at(const K &key) const
{
   	return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
V &HashMap<K, V, Hash, KeyFunction>::operator[](const K &key)
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
const V &HashMap<K, V, Hash, KeyFunction>::operator[](const K &key) const
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::begin() -> iterator
{
    return iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::end() -> iterator
{
    return iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::begin() const -> const_iterator
{
    return const_iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::end() const -> const_iterator
{
    return const_iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::cbegin() const -> const_iterator
{
    return const_iterator(buckets.cbegin(), buckets.cend());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::cend() const -> const_iterator
{
    return const_iterator(buckets.cend(), buckets.cend());
}

#pragma region bucket_interface

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::begin(size_type bucket) -> local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::end(size_type bucket) -> local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::begin(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::end(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::cbegin(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::cend(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getBucketCount() const -> size_type
{
    return buckets.getSize();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getBucketSize(size_type bucket) const -> List<value_type>::size_type
{
    return buckets[bucket].getSize();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getBucket(const K &key) const -> size_type
{
    return hashFunction(key) % getBucketCount();
}

#pragma endregion bucket_interface

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getKeyEqual() const -> key_equal {
	return keyEqualFunction;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getHashFunction() const -> hasher {
	return hashFunction;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
float HashMap<K, V, Hash, KeyFunction>::countLoadFactor() const
{
    return static_cast<float>(getSize()) / getBucketCount();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
void HashMap<K, V, Hash, KeyFunction>::rebuild()
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

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::insert(List<List<value_type>> &buckets, value_type &entry) -> std::pair<iterator, bool>
{
    size_t hash = hashFunction(entry.first);
    size_type index = hash % buckets.getSize();
    auto &bucket = buckets[index];

    ListIterator<value_type> res = bucket.pushFront(entry);
    return std::make_pair(iterator(buckets.begin() + index, buckets.end(), res), true);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getNextPrime(size_type size) const -> size_type
{
    while (size < std::numeric_limits<size_type>::max() && !isPrime(++size))
        ;
    return size;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
bool HashMap<K, V, Hash, KeyFunction>::isPrime(size_type value) const
{
    for (size_type i = 2; i < value; ++i)
        if (value % i == 0)
            return false;
    return true;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyFunction>
auto HashMap<K, V, Hash, KeyFunction>::getSize() const -> size_type
{
    size_type size = 0;
    for (auto &bucket : buckets)
        size += bucket.getSize();
    return size;
}
