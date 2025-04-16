#pragma once

#include "List.hpp"

template <typename T>
List<T>::List() {
}

template <typename T>
void List<T>::insertHead(const T &value) 
{
	head = std::make_shared<ListNode<T>>(value, head);
}

template <typename T>
void List<T>::insertTail(const T &value) 
{
    auto node = std::make_shared<ListNode<T>>(value, nullptr);

	auto tail = head;
	if(tail == nullptr)
	{
		head = node;
		return;
	}

	while(tail->next != nullptr)
		tail = tail->next;

	tail->next = node;
}

template <typename T>
bool List<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
auto List<T>::begin() -> iterator {
	return iterator(head);
}

template <typename T>
auto List<T>::end() -> iterator {
	return iterator(nullptr);
}
