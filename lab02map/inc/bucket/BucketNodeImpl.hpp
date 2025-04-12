#pragma once

#include "bucket/BucketNode.hpp"
#include <bucket/BucketConcepts.hpp>

template <typename K, typename V>
    requires HashAndEqual<K>
BucketNode<K, V>::BucketNode(const K key, const V value) : key(key), value(value), next(nullptr)
{
}

template <typename K, typename V>
    requires HashAndEqual<K>
void BucketNode<K, V>::setNext(const std::shared_ptr<BucketNode<K, V>> next)
{
    this->next = next;
}

template <typename K, typename V>
    requires HashAndEqual<K>
std::shared_ptr<BucketNode<K, V>> BucketNode<K, V>::getNext() const
{
    return this->next;
}

template <typename K, typename V>
    requires HashAndEqual<K>
bool BucketNode<K, V>::hasNext() const
{
    return this->next.get() != nullptr;
}

template <typename K, typename V>
    requires HashAndEqual<K>
K &BucketNode<K, V>::getKey()
{
    return this->key;
}

template <typename K, typename V>
    requires HashAndEqual<K>
V &BucketNode<K, V>::getValue()
{
    return this->value;
}
