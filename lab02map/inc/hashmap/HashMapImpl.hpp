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
    bucketCount = initialSize;
    sentinelNode = std::make_shared<HashMapNode<K, V>>(K(), V(), nullptr, nullptr, nullptr, 0);
    firstNode = sentinelNode;
    lastNode = sentinelNode;
    buckets = std::make_shared<std::shared_ptr<HashMapNode<K, V>>[]>(initialSize);
}

template <HashAndEqual K, MoveAndCopy V>
HashMap<K, V>::HashMap(HashMapIterator<K, V> &&begin, HashMapIterator<K, V> &&end) : HashMap()
{
    while (begin != end)
    {
        add(std::move(begin->key), std::move(begin->value));
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
    insertIntoBuckets(buckets, key, value);

    if (getLoadFactor() > loadFactorThreshold)
        rebuild();
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
		fixRemovedHeadTail(node);
        size--;
        return;
    }

    while (node != nullptr && node->next != nullptr)
    {
        if (node->next->key == key)
        {
            node->next = node->next->next;
            node->removeInOrder();
			fixRemovedHeadTail(node);
            size--;
            return;
        }
    }
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::clear()
{
    auto it = begin();
    while (it.isValid() && it != end())
    {
        auto next = it + std::size_t(1);
        remove(it->key);
        it = next;
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
    return keyHash(key) % bucketCount;
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
    return static_cast<float>(size) / bucketCount;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::rebuild()
{
    auto newBuckets = std::make_shared<std::shared_ptr<HashMapNode<K, V>>[]>(getNextPrime(getSize()));

    HashMapIterator<K, V> beginIt = begin();
    HashMapIterator<K, V> endIt = end();

    firstNode = sentinelNode;
    lastNode = sentinelNode;
    size = 0;
    for (auto it = beginIt; it != endIt; ++it)
        insertIntoBuckets(newBuckets, it->key, it->value);

    buckets = newBuckets;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::insertIntoBuckets(std::shared_ptr<std::shared_ptr<HashMapNode<K, V>>[]> buckets, const K &key,
                                      const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % bucketCount;

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
size_t HashMap<K, V>::getNextPrime(size_t size) const
{
    return size * 3;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::fixRemovedHeadTail(std::shared_ptr<HashMapNode<K, V>> node)
{
    if (node == firstNode)
    {
        firstNode->nextInOrder->previousInOrder = nullptr;
        firstNode = firstNode->nextInOrder;
        if (firstNode == nullptr)
            firstNode = sentinelNode;
    }
    else if (node == lastNode)
    {
        lastNode = lastNode->previousInOrder;
        sentinelNode->previousInOrder = lastNode;
    }
}

template <HashAndEqual K, MoveAndCopy V>
size_t HashMap<K, V>::getBucketCount()
{
    return buckets.size();
}
