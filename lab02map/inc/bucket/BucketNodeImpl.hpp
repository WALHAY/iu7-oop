#pragma once

#include <bucket/BucketNode.hpp>

template <typename T>
BucketNode<T>::BucketNode(const T &value, std::shared_ptr<BucketNode<T>> next)
{
    this->value = value;
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
