#pragma once

#include "hashmap/HashMap.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, typename V> HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, typename V> HashMap<K, V>::HashMap(const size_t initialSize)
{
    buckets.resize(initialSize);
}

template <HashAndEqual K, typename V> bool HashMap<K, V>::contains(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode> node = buckets[index];
    while (node != nullptr && node->key != key)
        node = node->next;

    return node != nullptr && node->key == key;
}

template <HashAndEqual K, typename V> void HashMap<K, V>::insert(const K &key, const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % buckets.size();

    std::shared_ptr<HashMapNode> newNode = std::make_shared<HashMapNode>(key, value, nullptr, nullptr, lastNode, hash);
    std::shared_ptr<HashMapNode> bucket = buckets[index];

    if (bucket == nullptr)
    {
        buckets[index] = newNode;
        return;
    }

    while (bucket != nullptr && bucket->next != nullptr)
        bucket = bucket->next;

    bucket->next = newNode;
    lastNode = newNode;
}

template <HashAndEqual K, typename V> std::optional<V> HashMap<K, V>::find(const K &key)
{
	size_t index = getEffectiveIndex(key);

	std::shared_ptr<HashMapNode> node = buckets[index];
	while(node != nullptr)
	{
		if(node->key == key)
			return node->value;

		node = node->next;
	}
	
	return std::nullopt;
}

template <HashAndEqual K, typename V> size_t HashMap<K, V>::getEffectiveIndex(const K &key)
{
    return keyHash(key) % buckets.size();
}

template <HashAndEqual K, typename V> size_t HashMap<K, V>::keyHash(const K &key)
{
    std::hash<K> hasher;
    return hasher(key);
}

template <HashAndEqual K, typename V> float HashMap<K, V>::calculateLoadFactor()
{
    return this->size / this->buckets.size();
}
