#pragma once

#include "collection/BaseIterator.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include <memory>

template <HashAndEqual K, typename V>
class HashMap;

template <HashAndEqual K, typename V>
class Iterator : public BaseIterator
{
  public:
    Iterator();
    Iterator(const HashMap<K, V> &map);
    Iterator(const Iterator<K, V> &iterator);
    Iterator(const std::weak_ptr<typename HashMap<K, V>::HashMapNode> &ptr);

    const HashMap<K, V>::HashMapNode &operator*() const;
    HashMap<K, V>::HashMapNode &operator*();
    const HashMap<K, V>::HashMapNode *operator->() const;
    HashMap<K, V>::HashMapNode *operator->();

    Iterator<K, V> operator+(int offset) const;
    Iterator<K, V> &operator++();
    Iterator<K, V> operator++(int);
    Iterator<K, V> &operator+=(int offset);

    Iterator<K, V> operator-(int offset) const;
    Iterator<K, V> &operator--();
    Iterator<K, V> operator--(int);
    Iterator<K, V> &operator-=(int offset);

	bool operator==(const Iterator<K, V> &other);
	bool operator!=(const Iterator<K, V> &other);

    HashMap<K, V>::HashMapNode *getPtr();
private:
	std::weak_ptr<typename HashMap<K, V>::HashMapNode> nodePtr;
};

#include <hashmap/HashMapIterImpl.hpp>
