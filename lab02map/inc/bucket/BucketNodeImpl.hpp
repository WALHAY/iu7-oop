#pragma once

#include <bucket/BucketNode.hpp>

template <typename T>
BucketNode<T>::BucketNode(const T &value, std::shared_ptr<BucketNode<T>> next) : value(value)
{
    this->next = next;
}

template <typename T>
T BucketNode<T>::getValue() const {
	return value;
}

template <typename T>
T &BucketNode<T>::getValueRef() {
	return value;
}

template <typename T>
const T &BucketNode<T>::getValueRef() const {
	return value;
}
