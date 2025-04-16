#pragma once

#include <cstddef>
#include <iterator>
#include <memory>

template <typename T>
class List;

template <typename T>
class ListNode;

template <typename T>
class ListIterator
{
	template <typename K, typename V>
	friend class HashMapIterator;

  public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = ListIterator<T>;
    using iterator_category = std::forward_iterator_tag;

    ListIterator();
    ListIterator(const List<T> &bucket);
    ListIterator(const ListIterator<T> &iterator);
    ListIterator(const std::shared_ptr<ListNode<T>> &node);

    reference operator*() const;
    pointer operator->() const;

    ListIterator<T> &operator++();
    ListIterator<T> operator++(int);
    ListIterator<T> operator+(size_type offset) const;
    ListIterator<T> &operator+=(size_type offset);

    ListIterator<T> &operator=(const ListIterator<T> &other);

    bool operator==(const ListIterator<T> &other) const;
    bool operator!=(const ListIterator<T> &other) const;

    bool isValid() const;

    operator bool() const;

  private:
    void validatePtr(int line) const;

    std::weak_ptr<ListNode<T>> nodePtr;
};

#include <list/iterators/ListIterImpl.hpp>
