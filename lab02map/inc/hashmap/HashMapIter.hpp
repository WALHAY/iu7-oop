#pragma once

#include "collection/BaseIterator.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"
#include <memory>

template <HashAndEqual K, typename V>
class HashMapIterator : public BaseIterator
{
  public:
    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const HashMapIterator<K, V> &iterator);
    HashMapIterator(const std::weak_ptr<HashMapNode<K, V>> &ptr);

    const HashMapNode<K, V> &operator*() const;
    HashMapNode<K, V> &operator*();
    const HashMapNode<K, V> *operator->() const;
    HashMapNode<K, V> *operator->();

    HashMapIterator<K, V> operator+(int offset) const;
    HashMapIterator<K, V> &operator++();
    HashMapIterator<K, V> operator++(int);
    HashMapIterator<K, V> &operator+=(int offset);

    HashMapIterator<K, V> operator-(int offset) const;
    HashMapIterator<K, V> &operator--();
    HashMapIterator<K, V> operator--(int);
    HashMapIterator<K, V> &operator-=(int offset);

    bool operator==(const HashMapIterator<K, V> &other);
    bool operator!=(const HashMapIterator<K, V> &other);

    HashMapNode<K, V> *getPtr();

  private:
    std::weak_ptr<HashMapNode<K, V>> nodePtr;
};

#include <hashmap/HashMapIterImpl.hpp>
