#pragma once

#include "hashmap/HashMap.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMap() : HashMap(8)
{
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMap(const size_t initialSize)
{
    firstNode = nullptr;
    lastNode = nullptr;
    buckets.resize(initialSize);
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMapNode::HashMapNode(K key, V value, std::shared_ptr<HashMapNode> next,
                                        std::shared_ptr<HashMapNode> previousInOrder,
                                        std::shared_ptr<HashMapNode> nextInOrder, size_t hash)
{
    this->key = key;
    this->value = value;
    this->next = next;
    this->previousInOrder = previousInOrder;
    this->nextInOrder = nextInOrder;
    this->hash = hash;
}

template <HashAndEqual K, typename V>
std::shared_ptr<typename HashMap<K, V>::HashMapNode> HashMap<K, V>::HashMapNode::getNext()
{
    return nextInOrder;
}

template <HashAndEqual K, typename V>
std::shared_ptr<typename HashMap<K, V>::HashMapNode> HashMap<K, V>::HashMapNode::getPrevious()
{
    return previousInOrder;
}

template <HashAndEqual K, typename V>
bool HashMap<K, V>::contains(const K &key)
{
    size_t index = getEffectiveIndex(key);

    std::shared_ptr<HashMapNode> node = buckets[index];
    while (node != nullptr && node->key != key)
        node = node->next;

    return node != nullptr && node->key == key;
}

template <HashAndEqual K, typename V>
void HashMap<K, V>::insert(const K &key, const V &value)
{
    size_t hash = keyHash(key);
    size_t index = hash % buckets.size();

    std::shared_ptr<HashMapNode> newNode = std::make_shared<HashMapNode>(key, value, nullptr, lastNode, nullptr, hash);
    std::shared_ptr<HashMapNode> bucket = buckets[index];

    if (firstNode == nullptr)
        firstNode = newNode;

    if (lastNode != nullptr)
    {
        lastNode->nextInOrder = newNode;
        newNode->previousInOrder = lastNode;
    }
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

    std::shared_ptr<HashMapNode> node = buckets[index];
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

    std::shared_ptr<HashMapNode> node = buckets[index];
    if (node != nullptr && node->key == key)
    {
        buckets[index] = node->next;
        std::shared_ptr<HashMapNode> previous = node->previousInOrder;
        previous->nextInOrder = node->nextInOrder;
        return;
    }

    while (node != nullptr && node->next != nullptr)
    {
        if (node->next->key == key)
        {
            std::shared_ptr<HashMapNode> previous = node->next->previousInOrder;
            previous->nextInOrder = node->next->nextInOrder;
            node->next = node->next->next;
            return;
        }
    }
}
template <HashAndEqual K, typename V>
Iterator<K, V> HashMap<K, V>::begin()
{
    return Iterator<K, V>(firstNode);
}

template <HashAndEqual K, typename V>
Iterator<K, V> HashMap<K, V>::end()
{
    return Iterator<K, V>(lastNode);
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
