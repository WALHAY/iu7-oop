#pragma once

#include <list/ListNode.hpp>

template <typename T>
ListNode<T>::ListNode(const T &value, std::shared_ptr<ListNode<T>> next) : value(value)
{
    this->next = next;
}

template <typename T>
T ListNode<T>::getValue() const {
	return value;
}

template <typename T>
T &ListNode<T>::getValueRef() {
	return value;
}

template <typename T>
const T &ListNode<T>::getValueRef() const {
	return value;
}
