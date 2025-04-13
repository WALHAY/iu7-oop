#pragma once

#include "hashmap/HashMapConcepts.hpp"
#include <cstddef>
#include <memory>

template <HashAndEqual K, MoveAndCopy V>
class HashMap;

template <HashAndEqual K, MoveAndCopy V>
class HashMapNode
{

    friend class HashMap<K, V>;

  public:
    HashMapNode(K key, V value, std::shared_ptr<HashMapNode> next, std::shared_ptr<HashMapNode> previousInOrder,
                std::shared_ptr<HashMapNode> nextInOrder, size_t hash);

    const K key;
    V value;

    std::shared_ptr<HashMapNode> getNext();
    std::shared_ptr<HashMapNode> getPrevious();

  private:
    std::shared_ptr<HashMapNode> next;
    std::shared_ptr<HashMapNode> previousInOrder;
    std::shared_ptr<HashMapNode> nextInOrder;

    size_t hash;
};

#include <hashmap/HashMapNodeImpl.hpp>
