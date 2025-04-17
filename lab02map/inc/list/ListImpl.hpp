#pragma once

#include "List.hpp"
#include <iostream>
#include <ostream>

template <typename T>
List<T>::List() {
}

template <typename T>
List<T>::List(size_type size) requires TrivialContstructor<T> {
	resize(size);
}

template <typename T>
List<T>::List(size_type size, const value_type& instance) requires CopyConstructible<T> {
	resize(size, instance);
}

template <typename T>
auto List<T>::insertHead(const T &value) -> iterator
{
	head = std::make_shared<ListNode<T>>(value, head);
	return iterator(head);
}

template <typename T>
void List<T>::removeHead() 
{
	if(head != nullptr)
		head = head->next;
}

template <typename T>
void List<T>::removeTail() 
{
	auto node = head;
	while(node != nullptr && node->next != nullptr && node->next->next != nullptr)
		node = node->next;

	node->next = nullptr;
}

template <typename T>
auto List<T>::insertTail(const T &value) -> iterator
{
    auto node = std::make_shared<ListNode<T>>(value, nullptr);

	auto tail = head;
	if(tail == nullptr)
	{
		head = node;
		return iterator(node);
	}

	while(tail->next != nullptr)
		tail = tail->next;

	tail->next = node;
	return iterator(node);
}

template <typename T>
bool List<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
auto List<T>::getSize() const -> size_type {
	auto node = head;
	size_type size = 0;
	while(node != nullptr)
	{
		size++;
		node = node->next;
	}
	return size;
}

template <typename T>
auto List<T>::at(size_type index) -> reference {
	auto node = head;
	while(index-- != 0 && node != nullptr)
		node = node->next;

	// TODO: throw error if invalid element

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
auto List<T>::getHead() -> reference {
	return head->value;
}

template <typename T>
auto List<T>::getHead() const -> const_reference {
	return getHead();
}

template <typename T>
auto List<T>::getTail() -> reference {
	auto node = head;
	while(node != nullptr && node->next != nullptr)
		node = node->next;

	return node->value;
}

template <typename T>
auto List<T>::getTail() const -> const_reference {
	return getTail();
}

template <typename T>
void List<T>::resize(size_type size) requires TrivialContstructor<T>
{
	head = nullptr;
	for(int i = 0; i < size; ++i)
		insertHead(T());
}

template <typename T>
void List<T>::resize(size_type size, const value_type& instance) requires CopyConstructible<T>
{
	head = nullptr;
	for(int i = 0; i < size; ++i)
		insertHead(T(instance));
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list) {
	this->head = list.head;
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
