#pragma once

#include <hashmap/HashMapExceptions.hpp>
#include <list/iterators/ConstListIter.hpp>

template <typename T>
ConstListIterator<T>::ConstListIterator()
{
}

template <typename T>
ConstListIterator<T>::ConstListIterator(const List<T> &map)
{
    nodePtr = map.lastNode;
}

template <typename T>
ConstListIterator<T>::ConstListIterator(const ConstListIterator<T> &iterator)
{
    nodePtr = iterator.nodePtr;
}

template <typename T>
ConstListIterator<T>::ConstListIterator(const std::shared_ptr<ListNode<T>> &node)
{
    nodePtr = node;
}

template <typename T>
ConstListIterator<T>::operator bool() const
{
    return isValid();
}

template <typename T>
auto ConstListIterator<T>::operator*() const -> reference
{
    validatePtr(__LINE__);
    return nodePtr.lock().get()->getValueRef();
}

template <typename T>
auto ConstListIterator<T>::operator->() const -> pointer
{
    validatePtr(__LINE__);
    return &(nodePtr.lock().get()->getValueRef());
}

// prefix
template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator++()
{
    validatePtr(__LINE__);
    nodePtr = nodePtr.lock()->getNext();
    return *this;
}

// postfix
template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator++(int)
{
    validatePtr(__LINE__);
    ConstListIterator<T> copy(*this);

    ++(*this);

    return copy;
}

template <typename T>
ConstListIterator<T> ConstListIterator<T>::operator+(size_type offset) const
{
	validatePtr(__LINE__);
    ConstListIterator<T> offsetIter(*this);
    while (offset-- > 0)
        ++offsetIter;
    return offsetIter;
}

template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator+=(size_type offset)
{
	validatePtr(__LINE__);
    while (offset-- > 0)
        ++(*this);
    return *this;
}

template <typename T>
ConstListIterator<T> &ConstListIterator<T>::operator=(const ConstListIterator<T> &other)
{
    nodePtr = other.nodePtr;
    return *this;
}

template <typename T>
bool ConstListIterator<T>::operator==(const ConstListIterator<T> &other) const
{
    return other.nodePtr.lock() == nodePtr.lock();
}

template <typename T>
bool ConstListIterator<T>::isValid() const
{
    return nodePtr.lock() != nullptr && !nodePtr.expired();
}

template <typename T>
void ConstListIterator<T>::validatePtr(int line) const
{
    if (!isValid())
        throw InvalidIterator(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, line);
}

template <typename T>
std::shared_ptr<ListNode<T>> ConstListIterator<T>::getPtr()
{
	return nodePtr.lock();
}

template <typename T>
const std::shared_ptr<ListNode<T>> ConstListIterator<T>::getPtr() const
{
	return nodePtr.lock();
}

static_assert(std::forward_iterator<ConstListIterator<int>>);
