#pragma once

#include <hashmap/HashMap.hpp>
#include <cmath>
#include <functional>

template <typename K, typename V>
    requires HashAndEqual<K>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <typename K, typename V>
    requires HashAndEqual<K>
HashMap<K, V>::HashMap(const size_t initialSize) : bucketsCount(initialSize)
{
    buckets.resize(initialSize);
}

template <typename K, typename V>
    requires HashAndEqual<K>
bool HashMap<K, V>::contains(const K& key)
{
	return buckets[getEffectiveIndex(key)].contains(key);
}

template <typename K, typename V>
    requires HashAndEqual<K>
void HashMap<K, V>::insert(const K& key, const V& value)
{
	size_t index = getEffectiveIndex(key);
	buckets[index].insert(key, value);
}

template <typename K, typename V>
    requires HashAndEqual<K>
size_t HashMap<K, V>::getEffectiveIndex(const K& key)
{
	return keyHash(key) % this->bucketsCount;
}

template <typename K, typename V>
    requires HashAndEqual<K>
size_t HashMap<K, V>::keyHash(const K& key)
{
	std::hash<K> hasher;
	return hasher(key);
}

template <typename K, typename V>
    requires HashAndEqual<K>
float HashMap<K, V>::calculateLoadFactor()
{
    float defaultFactor = static_cast<float>(this->size) / this->bucketsCount;
    float dynamicFactor = 1.0f + 1.0f / log2(this->size + 2);

    return defaultFactor * dynamicFactor;
}
