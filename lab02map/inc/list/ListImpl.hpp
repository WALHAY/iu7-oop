#pragma once

#include "List.hpp"

template <typename T>
List<T>::List() {
}

template <typename T>
List<T>::List(size_type size) {
	resize(size);
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
auto List<T>::at(size_type index) -> reference {
	auto node = head;
	while(--index != 0 && node != nullptr)
		node = node->next;

	return node->value;
}

template <typename T>
auto List<T>::at(size_type index) const -> const_reference {
	return at(index);
}

template <typename T>
auto List<T>::operator[](size_type index) -> reference {
	return at(index);
}

template <typename T>
auto List<T>::operator[](size_type index) const -> const_reference {
	return at(index);
}

template <typename T>
void List<T>::resize(size_type size)
{
	for(int i = 0; i < size; ++i)
	{
		head = nullptr;
		insertHead(T());
	}
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list) {
	this->head = list->head;
	return *this;
}

template <typename T>
auto List<T>::begin() -> iterator {
	return iterator(head);
}

template <typename T>
auto List<T>::end() -> iterator {
	return iterator(nullptr);
}
