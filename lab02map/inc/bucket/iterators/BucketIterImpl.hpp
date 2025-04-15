#pragma once

#include <bucket/iterators/BucketIter.hpp>
#include <hashmap/HashMapExceptions.hpp>

template <typename T>
BucketIterator<T>::BucketIterator(const Bucket<T> &map)
{
    nodePtr = map.lastNode;
}

template <typename T>
BucketIterator<T>::BucketIterator(const BucketIterator<T> &iterator)
{
    nodePtr = iterator.nodePtr;
}

template <typename T>
BucketIterator<T>::BucketIterator(const std::shared_ptr<BucketNode<T>> &node)
{
	nodePtr = node;
}

template <typename T>
BucketIterator<T>::operator bool()
{
    return isValid();
}

template <typename T>
auto BucketIterator<T>::operator*() const -> const_reference
{
    validatePtr(__LINE__);
    return getPtr()->getValueRef();
}

template <typename T>
auto BucketIterator<T>::operator*() -> reference
{
    validatePtr(__LINE__);
    return getPtr()->getValueRef();
}

template <typename T>
auto BucketIterator<T>::operator->() const -> const_pointer
{
    validatePtr(__LINE__);
    return getPtr()->getValueRef();
}

template <typename T>
auto BucketIterator<T>::operator->() -> pointer
{
    validatePtr(__LINE__);
    return getPtr()->getValueRef();
}

// prefix
template <typename T>
BucketIterator<T> &BucketIterator<T>::operator++()
{
    validatePtr(__LINE__);
    nodePtr = nodePtr.lock()->next;
    return *this;
}

// postfix
template <typename T>
BucketIterator<T> BucketIterator<T>::operator++(int)
{
    validatePtr(__LINE__);
    BucketIterator<T> oldIter(*this);

    ++(*this);

    return oldIter;
}

template <typename T>
BucketIterator<T> &BucketIterator<T>::operator=(const BucketIterator<T> &other)
{
    other.validatePtr(__LINE__);
    validatePtr(__LINE__);

    nodePtr = other.nodePtr;
    return *this;
}

template <typename T>
bool BucketIterator<T>::operator==(const BucketIterator<T> &other) const
{
    return other.nodePtr.lock() == nodePtr.lock();
}

template <typename T>
bool BucketIterator<T>::operator!=(const BucketIterator<T> &other) const
{
    return other.nodePtr.lock() != nodePtr.lock();
}

template <typename T>
bool BucketIterator<T>::isValid() const
{
    return nodePtr.lock() != nullptr && !nodePtr.expired();
}

template <typename T>
void BucketIterator<T>::validatePtr(int line) const
{
    if (!isValid())
        throw InvalidIterator(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, line);
}

template <typename T>
auto BucketIterator<T>::getPtr() const -> node_type
{
    return nodePtr.lock().get();
}
//
// static_assert(std::forward_iterator<BucketIterator<int>>);
