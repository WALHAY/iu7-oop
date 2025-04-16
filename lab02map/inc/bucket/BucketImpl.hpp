#pragma once

#include "Bucket.hpp"

template <typename T>
Bucket<T>::Bucket() {
}

template <typename T>
void Bucket<T>::insertHead(const T &value) 
{
	head = std::make_shared<BucketNode<T>>(value, head);
}

template <typename T>
void Bucket<T>::insertTail(const T &value) 
{
    auto node = std::make_shared<BucketNode<T>>(value, nullptr);

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
bool Bucket<T>::isEmpty() const {
	return head == nullptr;
}

template <typename T>
auto Bucket<T>::begin() -> iterator {
	return iterator(head);
}

template <typename T>
auto Bucket<T>::end() -> iterator {
	return iterator(nullptr);
}
