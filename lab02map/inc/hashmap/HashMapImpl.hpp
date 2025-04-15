#pragma once

#include "hashmap/HashMap.hpp"

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(const size_t initialSize)
{
    size = 0;
    buckets = std::make_shared<Bucket<value_type>[]>(initialSize);
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
	// TODO: implement
    return true;
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
	// TODO: implement
    size_t index = getBucket(key);

	auto it = std::find(begin(index), end(index), [&key](const K &l_key) {
		return key == l_key;
	});

	if(it == end(index))
		return end();

	return iterator(it);
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
auto HashMap<K, V>::begin() const -> iterator
{
    return HashMapIterator<K, V>(buckets);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::end() const -> iterator
{
    return HashMapIterator<K, V>(buckets + bucketCount);
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::begin(size_type bucket)  -> local_iterator
{
	return buckets[bucket].begin();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::end(size_type bucket)  -> local_iterator
{
    return buckets[bucket].end();
}

template <HashAndEqual K, MoveAndCopy V>
auto HashMap<K, V>::getBucket(const K &key) const -> size_type
{
    return getKeyHash(key) % getBucketCount();
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
    return static_cast<float>(size) / getBucketCount();
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::rebuild()
{
}

template <HashAndEqual K, MoveAndCopy V>
std::pair<typename HashMap<K, V>::iterator, bool> HashMap<K, V>::insert(std::shared_ptr<Bucket<value_type>[]> &buckets,
                                                                        const K &key, const V &value)
{
	// TODO: implement
	size_type bucket = getBucket(key);

    auto it = std::find_if(begin(bucket), end(bucket), [&key](const value_type &value) { return value.first == key; });

	if(it != end(bucket))
		return std::make_pair(iterator(), false);

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
size_t HashMap<K, V>::getBucketCount() const
{
    return bucketCount;
}
