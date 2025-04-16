#pragma once

#include <list/iterators/ListIter.hpp>
#include <hashmap/HashMapExceptions.hpp>

template <typename T>
ListIterator<T>::ListIterator()
{
}

template <typename T>
ListIterator<T>::ListIterator(const List<T> &map)
{
    nodePtr = map.lastNode;
}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T> &iterator)
{
    nodePtr = iterator.nodePtr;
}

template <typename T>
ListIterator<T>::ListIterator(const std::shared_ptr<ListNode<T>> &node)
{
	nodePtr = node;
}

template <typename T>
ListIterator<T>::operator bool() const
{
    return isValid();
}

template <typename T>
auto ListIterator<T>::operator*() const -> reference
{
    validatePtr(__LINE__);
    return nodePtr.lock().get()->getValueRef();
}

template <typename T>
auto ListIterator<T>::operator->() const -> pointer
{
    validatePtr(__LINE__);
    return &(nodePtr.lock().get()->getValueRef());
}

// prefix
template <typename T>
ListIterator<T> &ListIterator<T>::operator++()
{
    validatePtr(__LINE__);
    nodePtr = nodePtr.lock()->next;
    return *this;
}

// postfix
template <typename T>
ListIterator<T> ListIterator<T>::operator++(int)
{
    validatePtr(__LINE__);
    ListIterator<T> copy(*this);

    ++(*this);

    return copy;
}

template <typename T>
ListIterator<T> &ListIterator<T>::operator=(const ListIterator<T> &other)
{
    nodePtr = other.nodePtr;
    return *this;
}

template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T> &other) const
{
    return other.nodePtr.lock() == nodePtr.lock();
}

template <typename T>
bool ListIterator<T>::operator!=(const ListIterator<T> &other) const
{
	return !(*this == other);
}

template <typename T>
bool ListIterator<T>::isValid() const
{
    return nodePtr.lock() != nullptr && !nodePtr.expired();
}

template <typename T>
void ListIterator<T>::validatePtr(int line) const
{
    if (!isValid())
        throw InvalidIterator(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, line);
}

static_assert(std::forward_iterator<ListIterator<int>>);
