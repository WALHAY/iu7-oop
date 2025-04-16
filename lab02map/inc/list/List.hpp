#pragma once

#include <collection/BaseCollection.hpp>
#include <list/ListNode.hpp>
#include <list/iterators/ListIter.hpp>

template <typename T>
class List
{
  public:
    friend class ListNode<T>;

    using iterator = ListIterator<T>;
    using const_iterator = const ListIterator<T>;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    List();
	List(size_type size);

    void insertHead(const T &value);
    void insertTail(const T &value);

    void removeHead();
    void removeTail();

    iterator erase(const_iterator pos);

    reference getHead();
    const_reference getHead() const;

    reference getTail();
    const_reference getTail() const;

    void merge(List &&bucket);
    void merge(const List &bucket);

    bool isEmpty() const;

	void resize(size_type size);

    reference at(size_type index);
    const_reference at(size_type index) const;
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

	List<T> &operator=(const List<T> &list);

    /*
     * ITERATORS
     */
    iterator begin();
    iterator end();

  protected:
    std::shared_ptr<ListNode<T>> head;
};

#include <list/ListImpl.hpp>
