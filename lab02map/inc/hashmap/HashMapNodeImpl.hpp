#pragma once

#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"
#include <memory>

template <HashAndEqual K, MoveAndCopy V>
HashMapNode<K, V>::HashMapNode(K key, V value, std::shared_ptr<HashMapNode> next,
                               std::shared_ptr<HashMapNode> previousInOrder, std::shared_ptr<HashMapNode> nextInOrder,
                               size_t hash) : key(key)
{
    this->value = value;
    this->next = next;
    this->previousInOrder = previousInOrder;
    this->nextInOrder = nextInOrder;
    this->hash = hash;
}

template <HashAndEqual K, MoveAndCopy V>
std::shared_ptr<HashMapNode<K, V>> HashMapNode<K, V>::getNext()
{
    return nextInOrder;
}

template <HashAndEqual K, MoveAndCopy V>
std::shared_ptr<HashMapNode<K, V>> HashMapNode<K, V>::getPrevious()
{
    return previousInOrder;
}

template <HashAndEqual K, MoveAndCopy V>
void HashMapNode<K, V>::removeInOrder() {
	if(previousInOrder)
		previousInOrder->nextInOrder = nextInOrder;

	if(nextInOrder)
		nextInOrder->previousInOrder = previousInOrder;
}

