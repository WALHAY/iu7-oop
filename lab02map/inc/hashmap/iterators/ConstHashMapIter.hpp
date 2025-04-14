#pragma once

#include "collection/BaseIterator.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapNode.hpp"
#include "hashmap/HashMapExceptions.hpp"
#include <memory>

template <HashAndEqual K, MoveAndCopy V>
class ConstHashMapIterator : public BaseIterator
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using key_type = K;
    using value_type = V;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    using iterator = ConstHashMapIterator<K, V>;

    ConstHashMapIterator(const HashMap<K, V> &map);
    ConstHashMapIterator(const ConstHashMapIterator<K, V> &iterator);
    ConstHashMapIterator(const std::weak_ptr<HashMapNode<K, V>> &ptr);

	operator bool();

    const HashMapNode<K, V> &operator*() const;
    const HashMapNode<K, V> *operator->() const;

    ConstHashMapIterator<K, V> operator+(size_type offset) const;
    ConstHashMapIterator<K, V> &operator++();
    ConstHashMapIterator<K, V> operator++(int);
    ConstHashMapIterator<K, V> &operator+=(size_type offset);

    ConstHashMapIterator<K, V> operator-(size_type offset) const;
    ConstHashMapIterator<K, V> &operator--();
    ConstHashMapIterator<K, V> operator--(int);
    ConstHashMapIterator<K, V> &operator-=(size_type offset);

    ConstHashMapIterator<K, V> &operator=(const ConstHashMapIterator<K, V>& other);

    bool operator==(const ConstHashMapIterator<K, V> &other) const;
    bool operator!=(const ConstHashMapIterator<K, V> &other) const;

	bool isValid() const;

  private:
	void validatePtr(int line) const;

    std::weak_ptr<HashMapNode<K, V>> nodePtr;

    HashMapNode<K, V> *getPtr() const;
};

#include <hashmap/iterators/ConstHashMapIterImpl.hpp>
