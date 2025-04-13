#pragma once

#include "hashmap/HashMap.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(const size_t initialSize)
{
	size = 0;
    sentinelNode = std::make_shared<HashMapNode<K, V>>(K(), V(), nullptr, nullptr, nullptr, 0);
    firstNode = sentinelNode;
    lastNode = sentinelNode;
    buckets.resize(initialSize);
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(HashMapIterator<K, V>&& begin, HashMapIterator<K, V> &&end) : HashMap() {
	while(begin != end) {
		insert(std::move(begin->key), std::move(begin->value));
		++begin;
	}
}

template <HashAndEqual K, MoveAndCopy V>
bool HashMap<K, V>::contains(const K &key) const
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    while (node != nullptr && node->key != key)
        node = node->next;

    return node != nullptr && node->key == key;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::insert(const K &key, const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % buckets.size();

    std::shared_ptr<HashMapNode<K, V>> newNode =
        std::make_shared<HashMapNode<K, V>>(key, value, nullptr, lastNode, sentinelNode, hash);
    std::shared_ptr<HashMapNode<K, V>> bucket = buckets[index];

    if (firstNode == sentinelNode)
        firstNode = newNode;

    if (lastNode != sentinelNode)
    {
        lastNode->nextInOrder = newNode;
        newNode->previousInOrder = lastNode;
    }
    sentinelNode->previousInOrder = newNode;
    lastNode = newNode;
    size++;

    if (bucket == nullptr)
    {
        buckets[index] = newNode;
        return;
    }

    while (bucket != nullptr && bucket->next != nullptr)
        bucket = bucket->next;

    bucket->next = newNode;
}

template <HashAndEqual K, MoveAndCopy V>
HashMapIterator<K, V> HashMap<K, V>::find(const K &key) const
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    while (node != nullptr)
    {
        if (node->key == key)
            return HashMapIterator<K, V>(node);

        node = node->next;
    }

    return end();
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::remove(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    if (node != nullptr && node->key == key)
    {
        buckets[index] = node->next;
        node->removeInOrder();
		size--;
        return;
    }

    while (node != nullptr && node->next != nullptr)
    {
        if (node->next->key == key)
        {
            std::shared_ptr<HashMapNode<K, V>> previous = node->next->previousInOrder;
            node->removeInOrder();
			size--;
            return;
        }
    }
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::clear()
{
	for(auto it = begin(); it != end(); ++it)
	{
		remove(it->key);
	}
}

template <HashAndEqual K, MoveAndCopy V>
HashMapIterator<K, V> HashMap<K, V>::begin() const
{
    return HashMapIterator<K, V>(firstNode);
}

template <HashAndEqual K, MoveAndCopy V>
HashMapIterator<K, V> HashMap<K, V>::end() const
{
    return HashMapIterator<K, V>(sentinelNode);
}

template <HashAndEqual K, MoveAndCopy V>
size_t HashMap<K, V>::getEffectiveIndex(const K &key) const
{
    return keyHash(key) % buckets.size();
}

template <HashAndEqual K, MoveAndCopy V>
size_t HashMap<K, V>::keyHash(const K &key) const
{
    std::hash<K> hasher;
    return hasher(key);
}

template <HashAndEqual K, MoveAndCopy V>
float HashMap<K, V>::getLoadFactor() const
{
    return static_cast<float>(size) / this->buckets.size();
}
