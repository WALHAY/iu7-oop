#pragma once

#include <bucket/Bucket.hpp>

template <typename K, typename V>
    requires HashAndEqual<K>
Bucket<K, V>::Bucket() : BaseCollection(), head(nullptr)
{
}

template <typename K, typename V>
    requires HashAndEqual<K>
void Bucket<K, V>::insert(K key, V value)
{
    std::shared_ptr<BucketNode<K, V>> currentNode = this->head;
    std::shared_ptr<BucketNode<K, V>> newNode = std::make_shared<BucketNode<K, V>>(key, value);

	if(currentNode == nullptr)
	{
		this->head = newNode;
		return;
	}

    for (; currentNode->hasNext(); currentNode = currentNode->getNext())
        ;

    currentNode->setNext(newNode);
}

template <typename K, typename V>
    requires HashAndEqual<K>
bool Bucket<K, V>::contains(const K &key) const
{
    for (auto currentNode = this->head; currentNode != nullptr; currentNode = currentNode->getNext())
        if (currentNode->getKey() == key)
            return true;
    return false;
}

template <typename K, typename V>
    requires HashAndEqual<K>
std::optional<V> Bucket<K, V>::find(const K &key) const
{
    for (auto currentNode = this->head; currentNode != nullptr; currentNode = currentNode->getNext())
        if (currentNode->getKey() == key)
            return currentNode->getValue();
    return std::nullopt;
}

template <typename K, typename V>
    requires HashAndEqual<K>
void Bucket<K, V>::remove(const K &key)
{
    if (this->head->getKey() == key)
    {
        this->head = this->head->getNext();
        return;
    }

    std::shared_ptr<BucketNode<K, V>> currentNode = this->head;

    for (; currentNode->hasNext() && currentNode->getNext()->getKey() != key; currentNode = currentNode->getNext())
        ;

    if (currentNode->hasNext() && currentNode->getNext() != nullptr)
        currentNode->setNext(currentNode->getNext()->getNext());
}
