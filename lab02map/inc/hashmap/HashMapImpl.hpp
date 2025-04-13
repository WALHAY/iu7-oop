#pragma once

#include "hashmap/HashMap.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMap(const size_t initialSize)
{
    sentinelNode = std::make_shared<HashMapNode<K, V>>(K(), V(), nullptr, nullptr, nullptr, 0);
    firstNode = nullptr;
    lastNode = nullptr;
    buckets.resize(initialSize);
}
template <HashAndEqual K, typename V>
bool HashMap<K, V>::contains(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    while (node != nullptr && node->key != key)
        node = node->next;

    return node != nullptr && node->key == key;
}

template <HashAndEqual K, typename V>
void HashMap<K, V>::insert(const K &key, const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % buckets.size();

    std::shared_ptr<HashMapNode<K, V>> newNode =
        std::make_shared<HashMapNode<K, V>>(key, value, nullptr, lastNode, sentinelNode, hash);
    std::shared_ptr<HashMapNode<K, V>> bucket = buckets[index];

    if (firstNode == nullptr)
        firstNode = newNode;

    if (lastNode != nullptr)
    {
        lastNode->nextInOrder = newNode;
        newNode->previousInOrder = lastNode;
    }
    sentinelNode->previousInOrder = newNode;
    lastNode = newNode;

    if (bucket == nullptr)
    {
        buckets[index] = newNode;
        return;
    }

    while (bucket != nullptr && bucket->next != nullptr)
        bucket = bucket->next;

    bucket->next = newNode;
}

template <HashAndEqual K, typename V>
std::optional<V> HashMap<K, V>::find(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    while (node != nullptr)
    {
        if (node->key == key)
            return node->value;

        node = node->next;
    }

    return std::nullopt;
}

template <HashAndEqual K, typename V>
void HashMap<K, V>::remove(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode<K, V>> node = buckets[index];
    if (node != nullptr && node->key == key)
    {
        buckets[index] = node->next;
        std::shared_ptr<HashMapNode<K, V>> previous = node->previousInOrder;
        previous->nextInOrder = node->nextInOrder;
        return;
    }

    while (node != nullptr && node->next != nullptr)
    {
        if (node->next->key == key)
        {
            std::shared_ptr<HashMapNode<K, V>> previous = node->next->previousInOrder;
            previous->nextInOrder = node->next->nextInOrder;
            node->next = node->next->next;
            return;
        }
    }
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> HashMap<K, V>::begin() const
{
    return HashMapIterator<K, V>(firstNode);
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> HashMap<K, V>::end() const
{
    return HashMapIterator<K, V>(sentinelNode);
}

template <HashAndEqual K, typename V>
size_t HashMap<K, V>::getEffectiveIndex(const K &key)
{
    return keyHash(key) % buckets.size();
}

template <HashAndEqual K, typename V>
size_t HashMap<K, V>::keyHash(const K &key)
{
    std::hash<K> hasher;
    return hasher(key);
}

template <HashAndEqual K, typename V>
float HashMap<K, V>::calculateLoadFactor()
{
    return this->size / this->buckets.size();
}
