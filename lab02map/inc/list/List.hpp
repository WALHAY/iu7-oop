#pragma once

#include "list/ListConcepts.hpp"
#include <collection/BaseCollection.hpp>
#include <list/ListNode.hpp>
#include <list/iterators/ListIter.hpp>

template <typename T>
class List
{
  public:
    friend class ListNode<T>;

    using iterator = ListIterator<T>;
    using const_iterator = ListIterator<const T>;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    List();
	List(size_type size) requires TrivialContstructor<T>;
	List(size_type size, const value_type &) requires CopyConstructible<T>;

    iterator insertHead(const T &value);
    iterator insertTail(const T &value);

    void removeHead();
    void removeTail();

    iterator erase(const_iterator pos);

    reference getHead();
    const_reference getHead() const;

    reference getTail();
    const_reference getTail() const;

    bool isEmpty() const;

	void resize(size_type size) requires TrivialContstructor<T>;
	void resize(size_type size, const value_type& instance) requires CopyConstructible<T>;
	size_type getSize() const;

    reference at(size_type index);
    const_reference at(size_type index) const;
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

	List<T> &operator=(const List<T> &list);

    iterator begin();
    iterator end();

  protected:
    std::shared_ptr<ListNode<T>> head;
};

#include <list/ListImpl.hpp>
