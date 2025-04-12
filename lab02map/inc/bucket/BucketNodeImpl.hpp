#pragma once

#include "bucket/BucketNode.hpp"
#include <bucket/BucketConcepts.hpp>

template <typename K, typename V>
    requires HashAndEqual<K>
BucketNode<K, V>::BucketNode(K key, V value) : key(key), value(value), next(nullptr)
{
}

template <typename K, typename V>
    requires HashAndEqual<K>
void BucketNode<K, V>::setNext(std::shared_ptr<BucketNode<K, V>> next)
{
    return this->next = next;
}

template <typename K, typename V>
    requires HashAndEqual<K>
std::shared_ptr<BucketNode<K, V>> BucketNode<K, V>::getNext() const
{
    return this->next;
}

template <typename K, typename V>
    requires HashAndEqual<K>
bool BucketNode<K, V>::hasNext() const {
	return this->next != nullptr && this->next.get() != nullptr;
}

template <typename K, typename V>
    requires HashAndEqual<K>
K &BucketNode<K, V>::getKey() const
{
    return this->key;
}

template <typename K, typename V>
    requires HashAndEqual<K>
V &BucketNode<K, V>::getValue() const
{
    return this->value;
}
