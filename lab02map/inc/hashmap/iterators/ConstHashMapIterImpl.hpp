#pragma once

#include <hashmap/iterators/ConstHashMapIter.hpp>

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const HashMap<K, V> &map)
{
    nodePtr = map.lastNode;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const ConstHashMapIterator<K, V> &iterator)
{
    nodePtr = iterator.nodePtr;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V>::ConstHashMapIterator(const std::weak_ptr<HashMapNode<K, V>> &ptr)
{
    nodePtr = ptr;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V>::operator bool() {
	return isValid();
}

template <HashAndEqual K, MoveAndCopy V>
const HashMapNode<K, V> &ConstHashMapIterator<K, V>::operator*() const
{
	validatePtr(__LINE__);
    return *getPtr();
}

template <HashAndEqual K, MoveAndCopy V>
const HashMapNode<K, V> *ConstHashMapIterator<K, V>::operator->() const
{
	validatePtr(__LINE__);
    return getPtr();
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator+(size_t offset) const
{
	validatePtr(__LINE__);
	ConstHashMapIterator<K, V> newIter(*this);
	for(int i = 0; i < offset; ++i)
		++newIter;

    return newIter;
}

// prefix
template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator++()
{
	validatePtr(__LINE__);
    nodePtr = nodePtr.lock()->getNext();
    return *this;
}

// postfix
template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator++(int)
{
	validatePtr(__LINE__);
    ConstHashMapIterator<K, V> oldIter(*this);

    ++(*this);

    return oldIter;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator+=(size_type size)
{
	validatePtr(__LINE__);
    while (size--)
        ++(*this);
	return *this;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator-(size_type offset) const
{
	validatePtr(__LINE__);
	ConstHashMapIterator<K, V> newIter(*this);
	for(int i = 0; i < offset; ++i)
		--newIter;

    return newIter;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator--()
{
	validatePtr(__LINE__);
    nodePtr = nodePtr.lock()->getPrevious();
    return *this;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> ConstHashMapIterator<K, V>::operator--(int)
{
	validatePtr(__LINE__);
    ConstHashMapIterator<K, V> oldIter(*this);

    nodePtr = nodePtr.lock()->getPrevious();

    return oldIter;
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator-=(size_type size)
{
	validatePtr(__LINE__);

    while (size--)
        --(*this);
}

template <HashAndEqual K, MoveAndCopy V>
ConstHashMapIterator<K, V> &ConstHashMapIterator<K, V>::operator=(const ConstHashMapIterator<K, V>& other) {
	other.validatePtr(__LINE__);
	validatePtr(__LINE__);

	nodePtr = other.nodePtr;
	return *this;
}

template <HashAndEqual K, MoveAndCopy V>
bool ConstHashMapIterator<K, V>::operator==(const ConstHashMapIterator<K, V> &other) const
{
	other.validatePtr(__LINE__);
	validatePtr(__LINE__);

    return other.nodePtr.lock() == nodePtr.lock();
}

template <HashAndEqual K, MoveAndCopy V>
bool ConstHashMapIterator<K, V>::operator!=(const ConstHashMapIterator<K, V> &other) const
{
	other.validatePtr(__LINE__);
	validatePtr(__LINE__);

    return other.nodePtr.lock() != nodePtr.lock();
}

template <HashAndEqual K, MoveAndCopy V>
bool ConstHashMapIterator<K, V>::isValid() const {
	return nodePtr.lock() != nullptr && !nodePtr.expired();
}

template <HashAndEqual K, MoveAndCopy V>
void ConstHashMapIterator<K, V>::validatePtr(int line) const {
	if(!isValid())
		throw InvalidIterator(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, line);

}

template <HashAndEqual K, MoveAndCopy V>
HashMapNode<K, V> *ConstHashMapIterator<K, V>::getPtr() const
{
    return nodePtr.lock().get();
}
