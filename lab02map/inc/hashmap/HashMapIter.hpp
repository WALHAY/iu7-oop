#pragma once

#include "collection/BaseIterator.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"
#include <memory>

template <HashAndEqual K, MoveAndCopy V>
class HashMapIterator : public BaseIterator
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using key_type = K;
    using value_type = V;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    using iterator = HashMapIterator<K, V>;

    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const HashMapIterator<K, V> &iterator);
    HashMapIterator(const std::weak_ptr<HashMapNode<K, V>> &ptr);

	operator bool();

    const HashMapNode<K, V> &operator*() const;
    HashMapNode<K, V> &operator*();
    const HashMapNode<K, V> *operator->() const;
    HashMapNode<K, V> *operator->();

    HashMapIterator<K, V> operator+(size_type offset) const;
    HashMapIterator<K, V> &operator++();
    HashMapIterator<K, V> operator++(int);
    HashMapIterator<K, V> &operator+=(size_type offset);

    HashMapIterator<K, V> operator-(size_type offset) const;
    HashMapIterator<K, V> &operator--();
    HashMapIterator<K, V> operator--(int);
    HashMapIterator<K, V> &operator-=(size_type offset);

    bool operator==(const HashMapIterator<K, V> &other);
    bool operator!=(const HashMapIterator<K, V> &other);

	bool isValid();

  private:
    std::weak_ptr<HashMapNode<K, V>> nodePtr;

    HashMapNode<K, V> *getPtr();
};

#include <hashmap/HashMapIterImpl.hpp>
