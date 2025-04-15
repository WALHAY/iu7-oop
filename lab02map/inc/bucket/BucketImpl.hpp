#pragma once

#include <bucket/Bucket.hpp>

template <typename T>
Bucket<T>::Bucket() {
	sentinelNode = std::make_shared<BucketNode<T>>(T(), nullptr);
}

template <typename T>
void Bucket<T>::insertHead(const T &value) 
{
	head = std::make_shared<BucketNode<T>>(value, head);
}

template <typename T>
void Bucket<T>::insertTail(const T &value) 
{
    auto node = std::make_shared<BucketNode<T>>(value, head);

	auto tail = head;
	while(tail != nullptr && tail->next != sentinelNode)
		tail = tail->next;

	if(tail == nullptr)
	{
		head = node;
		node->next = sentinelNode;
		return;
	}

	tail->next = node;
	tail = node;
	node->next = sentinelNode;
}

template <typename T>
auto Bucket<T>::begin() -> iterator {
	return iterator(head);
}

template <typename T>
auto Bucket<T>::end() -> iterator {
	return iterator(sentinelNode);
}
