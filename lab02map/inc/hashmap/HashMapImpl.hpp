#pragma once

#include "hashmap/HashMap.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapExceptions.hpp"
#include "hashmap/HashMapNode.hpp"
#include <iostream>

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
    buckets = std::vector<std::shared_ptr<HashMapNode<K, V>>>(initialSize);
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
std::pair<typename HashMap<K, V>::iterator, bool> HashMap<K, V>::emplace(const K &key, const V &value)
{
    if (getLoadFactor() > loadFactorThreshold)
        rebuild();

    return insert(buckets, key, value);
}

template <HashAndEqual K, MoveAndCopy V>
HashMapIterator<K, V> HashMap<K, V>::find(const K &key)
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
HashMap<K, V>::iterator HashMap<K, V>::erase(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    if (node != nullptr && node->key == key)
    {
        buckets[index] = node->next;
        node->removeInOrder();
        fixRemovedHeadTail(node);
        size--;
        return node->nextInOrder;
    }

    while (node != nullptr && node->next != nullptr)
    {
        if (node->next->key == key)
        {
            node->next = node->next->next;
            node->removeInOrder();
            fixRemovedHeadTail(node);
            size--;
            return node->nextInOrder;
        }
    }
    return nullptr;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::clear()
{
    auto it = begin();
    while (it.isValid() && it != end())
    {
        auto next = it + std::size_t(1);
        erase(it->key);
        it = next;
    }
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
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, __LINE__);

    return it->value;
}

template <HashAndEqual K, MoveAndCopy V>
V &HashMap<K, V>::operator[](const K &key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, __LINE__);

    return it->value;
}

template <HashAndEqual K, MoveAndCopy V>
V &HashMap<K, V>::operator[](K &&key)
{
    auto it = find(key);
    if (it == end())
        throw OutOfRangeException(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, __LINE__);

    return it->value;
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
    return keyHash(key) % getBucketCount();
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
    return static_cast<float>(size) / getBucketCount();
}

template <HashAndEqual K, MoveAndCopy V>
void HashMap<K, V>::rebuild()
{
    auto newBuckets = std::vector<std::shared_ptr<HashMapNode<K, V>>>(getNextPrime(getBucketCount()));

    HashMapIterator<K, V> beginIt = begin();
    HashMapIterator<K, V> endIt = end();

    firstNode = sentinelNode;
    lastNode = sentinelNode;
	size = 0;
    for (auto it = beginIt; it != endIt; ++it)
        insert(newBuckets, it->key, it->value);

    buckets = newBuckets;
}

template <HashAndEqual K, MoveAndCopy V>
std::pair<typename HashMap<K, V>::iterator, bool> HashMap<K, V>::insert(std::vector<std::shared_ptr<HashMapNode<K, V>>> &buckets, const K &key,
                                              const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % buckets.size();

    std::shared_ptr<HashMapNode<K, V>> bucket = buckets[index];
    std::shared_ptr<HashMapNode<K, V>> node =
        std::make_shared<HashMapNode<K, V>>(key, value, nullptr, lastNode, sentinelNode, hash);

    if (firstNode == sentinelNode)
        firstNode = node;

    if (lastNode != sentinelNode)
    {
        lastNode->nextInOrder = node;
        node->previousInOrder = lastNode;
    }

    lastNode = node;
    lastNode->nextInOrder = sentinelNode;
    sentinelNode->previousInOrder = lastNode;
    size++;

    while (bucket != nullptr && bucket->next != nullptr)
    {
        if (bucket->key == key)
            return std::make_pair(HashMap<K, V>::iterator(bucket), false);

        bucket = bucket->next;
    }

    if (bucket == nullptr)
        buckets[index] = node;
    else
        bucket->next = node;

    return std::make_pair(HashMap<K, V>::iterator(node), true);
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
size_t HashMap<K, V>::getBucketCount() const
{
    return buckets.size();
}
