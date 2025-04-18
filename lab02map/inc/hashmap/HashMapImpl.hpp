#pragma once

#include "hashmap/HashMap.hpp"
#include <cmath>

#pragma region constructors

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
HashMap<K, V, Hash, KeyEqual>::HashMap() : HashMap(8)
{
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
HashMap<K, V, Hash, KeyEqual>::HashMap(size_t size) : hashFunction(Hash()), keyEqualFunction(KeyEqual())
{
    buckets = List<List<value_type>>(size);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
HashMap<K, V, Hash, KeyEqual>::HashMap(std::initializer_list<value_type> list) : HashMap(list.begin(), list.end())
{
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
template <ConvertibleIterator<typename HashMap<K, V, Hash, KeyEqual>::value_type> Iter>
HashMap<K, V, Hash, KeyEqual>::HashMap(Iter &&begin, Iter &&end) : HashMap()
{
    for (Iter it = begin; it != end; ++it)
        emplace(*it);
}

#pragma endregion constructors

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
HashMap<K, V, Hash, KeyEqual> &HashMap<K, V, Hash, KeyEqual>::operator=(const hashmap &map) {
	buckets = List<List<value_type>>(map->buckets);
}

#pragma region iterators

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::begin() -> iterator
{
    return iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::end() -> iterator
{
    return iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::begin() const -> const_iterator
{
    return const_iterator(buckets.begin(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::end() const -> const_iterator
{
    return const_iterator(buckets.end(), buckets.end());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::cbegin() const -> const_iterator
{
    return const_iterator(buckets.cbegin(), buckets.cend());
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::cend() const -> const_iterator
{
    return const_iterator(buckets.cend(), buckets.cend());
}

#pragma endregion iterators

#pragma region modifiers

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
void HashMap<K, V, Hash, KeyEqual>::clear()
{
    for (auto &bucket : buckets)
        bucket.clear();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::emplace(const K &key, const V &value) -> std::pair<iterator, bool>
{
    return emplace(std::make_pair(key, value));
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::emplace(value_type entry) -> std::pair<iterator, bool>
{
    if (countLoadFactor() > maxLoadFactor)
        rehash(getBucketCount() + 1);

    return insert(buckets, entry);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
bool HashMap<K, V, Hash, KeyEqual>::erase(const K &key)
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });
    if (it == end(index))
        return false;

    buckets[index].erase(it);

    return true;
}

#pragma endregion modifiers

#pragma region lookup

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
V &HashMap<K, V, Hash, KeyEqual>::at(const K &key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __PRETTY_FUNCTION__, __LINE__);

    return it->second;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
const V &HashMap<K, V, Hash, KeyEqual>::at(const K &key) const
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
V &HashMap<K, V, Hash, KeyEqual>::operator[](const K &key)
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
const V &HashMap<K, V, Hash, KeyEqual>::operator[](const K &key) const
{
    return at(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::find(const K &key) -> iterator
{
    size_type index = getBucket(key);

    auto it = std::find_if(begin(index), end(index), [&key](const value_type &value) { return value.first == key; });

    return iterator(buckets.begin() + index, buckets.end(), it);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::find(const K &key) const -> const_iterator
{
    return find(key);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
bool HashMap<K, V, Hash, KeyEqual>::contains(const K &key) const
{
    size_type bucket = getBucket(key);

    return false;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
bool HashMap<K, V, Hash, KeyEqual>::contains(K &&key) const
{
    return contains(key);
}

#pragma endregion lookup

#pragma region bucket interface

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::begin(size_type bucket) -> local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::end(size_type bucket) -> local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::begin(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::end(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::cbegin(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].begin();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::cend(size_type bucket) const -> const_local_iterator
{
    return buckets[bucket].end();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getBucketCount() const -> size_type
{
    return buckets.getSize();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getBucketSize(size_type bucket) const -> List<value_type>::size_type
{
    return buckets[bucket].getSize();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getBucket(const K &key) const -> size_type
{
    return hashFunction(key) % getBucketCount();
}

#pragma endregion bucket interface

#pragma region hash policy

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
void HashMap<K, V, Hash, KeyEqual>::setMaxLoadFactor(float maxLoadFactor)
{
	this->maxLoadFactor = maxLoadFactor;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
float HashMap<K, V, Hash, KeyEqual>::getMaxLoadFactor() const
{
	return maxLoadFactor;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
void HashMap<K, V, Hash, KeyEqual>::rehash(size_type count) {
	size_type nextSize = getNextPrime(std::max(static_cast<size_type>(getSize() / getMaxLoadFactor()), count));

	List<List<value_type>> newBuckets(nextSize);

	for(auto it = begin(); it != end(); ++it)
	{
		insert(newBuckets, *it);
	}

	buckets = newBuckets;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
void HashMap<K, V, Hash, KeyEqual>::reserve(size_type count) 
{
	rehash(std::ceil(count / getMaxLoadFactor()));
}

#pragma endregion hash policy

#pragma region observers

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getKeyEqual() const -> key_equal
{
    return keyEqualFunction;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getHashFunction() const -> hasher
{
    return hashFunction;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getSize() const -> size_type
{
    size_type size = 0;
    for (auto &bucket : buckets)
        size += bucket.getSize();
    return size;
}

#pragma endregion observers

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
float HashMap<K, V, Hash, KeyEqual>::countLoadFactor() const
{
    return static_cast<float>(getSize()) / getBucketCount();
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::insert(List<List<value_type>> &buckets, value_type &entry)
    -> std::pair<iterator, bool>
{
    size_t hash = hashFunction(entry.first);
    size_type index = hash % buckets.getSize();
    auto &bucket = buckets[index];

    ListIterator<value_type> res = bucket.pushFront(entry);
    return std::make_pair(iterator(buckets.begin() + index, buckets.end(), res), true);
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
auto HashMap<K, V, Hash, KeyEqual>::getNextPrime(size_type size) const -> size_type
{
    while (size < std::numeric_limits<size_type>::max() && !isPrime(++size))
        ;
    return size;
}

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
bool HashMap<K, V, Hash, KeyEqual>::isPrime(size_type value) const
{
    for (size_type i = 2; i < value; ++i)
        if (value % i == 0)
            return false;
    return true;
}

