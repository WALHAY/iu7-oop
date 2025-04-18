#pragma once

#include "list/ListConcepts.hpp"
#include "list/iterators/ConstListIter.hpp"
#include <collection/BaseCollection.hpp>
#include <list/ListNode.hpp>
#include <list/iterators/ListIter.hpp>

template <typename T>
class List : public BaseCollection
{
  public:
    friend class ListNode<T>;

    using iterator = ListIterator<T>;
    using const_iterator = ConstListIterator<T>;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    List();
    List(std::initializer_list<T> list);
    List(const List<T> &list) = default;
    List(List<T> &&list) noexcept = default;
    explicit List(size_type size)
        requires DefaultConstructible<T>;
    List(size_type size, const value_type &instance)
        requires CopyConstructible<T>;

    template <ConvertibleIterator<T> Iter>
    List(Iter &&begin, Iter &&end);

    iterator pushFront(const T &value);
    iterator pushBack(const T &value);

    void popFront() noexcept;
    void popBack() noexcept;

    void erase(const iterator& pos);

    virtual void clear() noexcept override;

    reference getFront();
    const_reference getFront() const;

    reference getBack();
    const_reference getBack() const;

    void resize(size_type size)
        requires DefaultConstructible<T>;
    void resize(size_type size, const value_type &instance)
        requires CopyConstructible<T>;

    virtual size_type getSize() const noexcept override;

    reference at(size_type index);
    const_reference at(size_type index) const;
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    List<T> &operator=(const List<T> &list);
    List<T> &operator=(List<T> &&list) noexcept = default;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

  protected:
	void validateGet(int line) const;
	void validateIndex(int line) const;

    void eraseNode(std::shared_ptr<ListNode<T>> node);

    std::shared_ptr<ListNode<T>> head;
};

#include <list/ListImpl.hpp>
