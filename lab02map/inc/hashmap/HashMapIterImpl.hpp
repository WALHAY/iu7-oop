#pragma once

#include <hashmap/HashMapIter.hpp>
#include <iostream>

template <HashAndEqual K, typename V>
Iterator<K, V>::Iterator()
{
}

template <HashAndEqual K, typename V>
Iterator<K, V>::Iterator(const HashMap<K, V> &map)
{
    nodePtr = map.lastNode;
}

template <HashAndEqual K, typename V>
Iterator<K, V>::Iterator(const Iterator<K, V> &iterator)
{
    nodePtr = iterator->nodePtr;
}

template <HashAndEqual K, typename V>
Iterator<K,V>::Iterator(const std::weak_ptr<typename HashMap<K, V>::HashMapNode> &ptr) {
	nodePtr = ptr;
}

template <HashAndEqual K, typename V>
const HashMap<K, V>::HashMapNode &Iterator<K,V>::operator*() const
{
	return *getPtr();
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMapNode &Iterator<K,V>::operator*()
{
	return *getPtr();
}

template <HashAndEqual K, typename V>
const HashMap<K, V>::HashMapNode *Iterator<K,V>::operator->() const
{
	return getPtr();
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMapNode *Iterator<K,V>::operator->()
{
	return getPtr();
}

// prefix
template <HashAndEqual K, typename V>
Iterator<K, V> &Iterator<K, V>::operator++()
{
	nodePtr = nodePtr.lock()->getNext();
    return *this;
}

// postfix
template <HashAndEqual K, typename V>
Iterator<K, V> Iterator<K, V>::operator++(int)
{
    Iterator<K, V> oldIter(*this);

    ++(*this);

    return oldIter;
}

template <HashAndEqual K, typename V>
Iterator<K, V> &Iterator<K, V>::operator+=(int size)
{
    while (size--)
        ++(*this);
}

template <HashAndEqual K, typename V>
Iterator<K, V> Iterator<K, V>::operator-(int offset) const
{
}

template <HashAndEqual K, typename V>
Iterator<K, V> &Iterator<K, V>::operator--()
{
}

template <HashAndEqual K, typename V>
Iterator<K, V> Iterator<K, V>::operator--(int)
{
}

template <HashAndEqual K, typename V>
Iterator<K, V> &Iterator<K, V>::operator-=(int size)
{
}

template <HashAndEqual K, typename V>
bool Iterator<K, V>::operator==(const Iterator<K, V> &other) {
	return other.nodePtr.lock() == nodePtr.lock();
}

template <HashAndEqual K, typename V>
bool Iterator<K, V>::operator!=(const Iterator<K, V> &other) {
	return other.nodePtr.lock() != nodePtr.lock();
}

template <HashAndEqual K, typename V>
HashMap<K, V>::HashMapNode *Iterator<K, V>::getPtr()
{
    return nodePtr.lock().get();
}
