#pragma once

#include <hashmap/HashMapIter.hpp>

template <HashAndEqual K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMap<K, V> &map)
{
    nodePtr = map.lastNode;
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V>::HashMapIterator(const HashMapIterator<K, V> &iterator)
{
    nodePtr = iterator->nodePtr;
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V>::HashMapIterator(const std::weak_ptr<HashMapNode<K, V>> &ptr)
{
    nodePtr = ptr;
}

template <HashAndEqual K, typename V>
const HashMapNode<K, V> &HashMapIterator<K, V>::operator*() const
{
    return *getPtr();
}

template <HashAndEqual K, typename V>
HashMapNode<K, V> &HashMapIterator<K, V>::operator*()
{
    return *getPtr();
}

template <HashAndEqual K, typename V>
const HashMapNode<K, V> *HashMapIterator<K, V>::operator->() const
{
    return getPtr();
}

template <HashAndEqual K, typename V>
HashMapNode<K, V> *HashMapIterator<K, V>::operator->()
{
    return getPtr();
}

// prefix
template <HashAndEqual K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator++()
{
    nodePtr = nodePtr.lock()->getNext();
    return *this;
}

// postfix
template <HashAndEqual K, typename V>
HashMapIterator<K, V> HashMapIterator<K, V>::operator++(int)
{
    HashMapIterator<K, V> oldIter(*this);

    ++(*this);

    return oldIter;
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator+=(size_type size)
{
    while (size--)
        ++(*this);
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> HashMapIterator<K, V>::operator-(size_type offset) const
{
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator--()
{
    nodePtr = nodePtr.lock()->getPrevious();
    return *this;
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> HashMapIterator<K, V>::operator--(int)
{
    HashMapIterator<K, V> oldIter(*this);

    nodePtr = nodePtr.lock()->getPrevious();

    return oldIter;
}

template <HashAndEqual K, typename V>
HashMapIterator<K, V> &HashMapIterator<K, V>::operator-=(size_type size)
{
    while (size--)
        --(*this);
}

template <HashAndEqual K, typename V>
bool HashMapIterator<K, V>::operator==(const HashMapIterator<K, V> &other)
{
    return other.nodePtr.lock() == nodePtr.lock();
}

template <HashAndEqual K, typename V>
bool HashMapIterator<K, V>::operator!=(const HashMapIterator<K, V> &other)
{
    return other.nodePtr.lock() != nodePtr.lock();
}

template <HashAndEqual K, typename V>
HashMapNode<K, V> *HashMapIterator<K, V>::getPtr()
{
    return nodePtr.lock().get();
}
