#pragma once

#include "hashmap/HashMap.hpp"
#include <algorithm>

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(const size_t initialSize)
{
    size = 0;
    buckets = List<List<value_type>>(initialSize);
    bucketCount = initialSize;
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(const std::initializer_list<std::pair<K, V>> list) : HashMap(list.size())
{
    for (auto &pair : list)
        emplace(pair);
}

template <HashAndEqual K, MoveAndCopy V>
bool HashMap<K, V>::contains(const K &key) const
{
    size_type bucket = getList(key);

    return std::any_of(cbegin(bucket), cend(bucket), [&key](const value_type &value) { return value.first == key; });
}

template <HashAndEqual K, MoveAndCopy V>
bool HashMap<K, V>::contains(K &&key) const
{
    return contains(key);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::emplace(const K &key, const V &value) -> std::pair<iterator, bool>
{
    // TODO: implement
    if (countLoadFactor() > loadFactorThreshold)
        rebuild();

    return insert(buckets, key, value);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::find(const K &key) -> iterator
{
    size_t bucket = getList(key);

    auto it = std::find_if(begin(bucket), end(bucket), [&key](const K &l_key) { return key == l_key; });

    if (it == end(bucket))
        return end();

    return iterator(it);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::find(K &&key) -> iterator {
	return find(key);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::find(const K &key) const -> const_iterator
{
    size_t bucket = getList(key);

    auto it = std::find_if(cbegin(bucket), cend(bucket), [&key](const K &l_key) { return key == l_key; });

    if (it == end(bucket))
        return end();

    return iterator(it);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::find(K &&key) const -> const_iterator {
	return find(key);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::emplace(std::pair<K, V> entry) -> std::pair<iterator, bool>
{
    return emplace(entry.first, entry.second);
}

template <HashAndEqual K, MoveAndCopy V>
bool HashMap<K, V>::erase(const K &key)
{
    // TODO: implement
    return true;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::clear()
{
}

template <HashAndEqual K, MoveAndCopy V>
V &HashMap<K, V>::at(const K &key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, __LINE__);

    return it->value;
}

template <HashAndEqual K, MoveAndCopy V>
const V &HashMap<K, V>::at(const K &key) const
{
    return at(key);
}

template <HashAndEqual K, MoveAndCopy V>
V &HashMap<K, V>::operator[](const K &key)
{
    return at(key);
}

template <HashAndEqual K, MoveAndCopy V>
V &HashMap<K, V>::operator[](K &&key)
{
    return at(key);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::begin() -> iterator
{
    return HashMapIterator<K, V>(*this);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::end() -> iterator
{
    return HashMapIterator<K, V>(*this, bucketCount);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::begin(size_type bucket) -> local_iterator
{
    return buckets.get()[bucket].begin();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::end(size_type bucket) -> local_iterator
{
    return buckets.get()[bucket].end();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::cbegin(size_type bucket) const -> const_local_iterator
{
    return buckets.get()[bucket].begin();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::cend(size_type bucket) const -> const_local_iterator
{
    return buckets.get()[bucket].end();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::getList(const K &key) const -> size_type
{
    return getKeyHash(key) % getListCount();
}

template <HashAndEqual K, MoveAndCopy V>
size_t HashMap<K, V>::getKeyHash(const K &key) const
{
    std::hash<K> hasher;
    return hasher(key);
}

template <HashAndEqual K, MoveAndCopy V>
float HashMap<K, V>::countLoadFactor() const
{
    return static_cast<float>(size) / getListCount();
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::rebuild()
{
}

template <HashAndEqual K, MoveAndCopy V>
std::pair<typename HashMap<K, V>::iterator, bool> HashMap<K, V>::insert(List<List<value_type>> &buckets,
                                                                        const K &key, const V &value)
{
    size_type bucket = getList(key);

    auto it = std::find_if(begin(bucket), end(bucket), [&key](const value_type &value) { return value.first == key; });

    if (it != end(bucket))
        return std::make_pair(iterator(), false);

    buckets[bucket].insertTail(std::make_pair(key, value));
    return std::make_pair(begin(), true);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::getNextPrime(size_type size) const -> size_type
{
    while (size < std::numeric_limits<size_type>::max() && !isPrime(++size))
        ;
    return size;
}

template <HashAndEqual K, MoveAndCopy V>
bool HashMap<K, V>::isPrime(size_type value) const
{
    for (size_type i = 2; i < value; ++i)
        if (value % i == 0)
            return false;
    return true;
}

template <HashAndEqual K, MoveAndCopy V>
size_t HashMap<K, V>::getListCount() const
{
    return bucketCount;
}
