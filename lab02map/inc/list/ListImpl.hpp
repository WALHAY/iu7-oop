#pragma once

#include "List.hpp"
#include <list/ListExceptions.hpp>

template <typename T>
List<T>::List()
{
}

template <typename T>
template <ConvertibleIterator<T> Iter>
List<T>::List(const Iter &begin, const Iter &end)
{
    for (auto it = begin; it != end; ++it)
        pushBack(*it);
}

template <typename T>
List<T>::List(const std::initializer_list<T> &list) : List(list.begin(), list.end())
{
}

template <typename T>
List<T>::List(size_type size)
    requires DefaultConstructible<T>
{
    resize(size);
}

template <typename T>
List<T>::List(size_type size, const value_type &instance)
    requires CopyConstructible<T>
{
    resize(size, instance);
}

template <typename T>
auto List<T>::pushFront(const T &value) -> iterator
{
    head = std::make_shared<ListNode<T>>(value, head);
    return iterator(head);
}

template <typename T>
void List<T>::popFront() noexcept
{
    if (head != nullptr)
        head = head->next;
}

template <typename T>
void List<T>::popBack() noexcept
{
    auto node = head;
    while (node != nullptr && node->next != nullptr && node->next->next != nullptr)
        node = node->next;

    node->next = nullptr;
}

template <typename T>
void List<T>::erase(iterator iterator)
{
    eraseNode(iterator.getPtr());
}

template <typename T>
void List<T>::eraseNode(std::shared_ptr<ListNode<T>> remove)
{
    if (remove == nullptr)
        return;

    auto node = head;
    while (node != nullptr)
    {
        if (node->next == remove)
        {
            node->next = remove->next;
        }
        node = node->next;
    }
}

template <typename T>
auto List<T>::pushBack(const T &value) -> iterator
{
	std::shared_ptr<ListNode<T>> node = nullptr;
    try
    {
        node = std::make_shared<ListNode<T>>(value, nullptr);
    }
    catch (std::bad_alloc e)
    {
		throw NodeAllocationException(__FILE_NAME__, typeid(*this).name(), __FUNCTION__, __LINE__);
		return end();
    }

    auto tail = head;
    if (tail == nullptr)
    {
        head = node;
        return iterator(node);
    }

    while (tail->next != nullptr)
        tail = tail->next;

    tail->next = node;
    return iterator(node);
}

template <typename T>
auto List<T>::getSize() const noexcept -> size_type
{
    auto node = head;
    size_type size = 0;
    while (node != nullptr)
    {
        size++;
        node = node->next;
    }
    return size;
}

template <typename T>
void List<T>::clear() noexcept
{
    head = nullptr;
}

template <typename T>
auto List<T>::at(size_type index) -> reference
{
    auto node = head;
    while (index-- != 0 && node != nullptr)
        node = node->next;

    if (node == nullptr && index != 0)
        throw InvalidIndexAccessException(__FILE_NAME__, typeid(*this).name(), __PRETTY_FUNCTION__, __LINE__);

    return node->value;
}

template <typename T>
auto List<T>::at(size_type index) const -> const_reference
{
    return at(index);
}

template <typename T>
auto List<T>::operator[](size_type index) -> reference
{
    return at(index);
}

template <typename T>
auto List<T>::operator[](size_type index) const -> const_reference
{
    return at(index);
}

template <typename T>
auto List<T>::getFront() noexcept -> reference
{
    return head->value;
}

template <typename T>
auto List<T>::getFront() const noexcept -> const_reference
{
    return getFront();
}

template <typename T>
auto List<T>::getBack() noexcept -> reference
{
    auto node = head;
    while (node != nullptr && node->next != nullptr)
        node = node->next;

    return node->value;
}

template <typename T>
auto List<T>::getBack() const noexcept -> const_reference
{
    return getBack();
}

template <typename T>
void List<T>::resize(size_type size)
    requires DefaultConstructible<T>
{
    head = nullptr;
    for (int i = 0; i < size; ++i)
        pushFront(T());
}

template <typename T>
void List<T>::resize(size_type size, const value_type &instance)
    requires CopyConstructible<T>
{
    head = nullptr;
    for (int i = 0; i < size; ++i)
        pushFront(T(instance));
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &list)
{
    head = nullptr;
    for (auto &it : list)
        pushBack(it);
    return *this;
}

template <typename T>
auto List<T>::begin() -> iterator
{
    return iterator(head);
}

template <typename T>
auto List<T>::end() -> iterator
{
    return iterator(nullptr);
}

template <typename T>
auto List<T>::begin() const -> const_iterator
{
    return const_iterator(head);
}

template <typename T>
auto List<T>::end() const -> const_iterator
{
    return const_iterator(nullptr);
}

template <typename T>
auto List<T>::cbegin() const -> const_iterator
{
    return const_iterator(head);
}

template <typename T>
auto List<T>::cend() const -> const_iterator
{
    return const_iterator(nullptr);
}
