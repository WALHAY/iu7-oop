#pragma once

#include <memory>

template <typename T>
class List;

template <typename T>
class ListIterator;

template <typename T>
class ListNode
{
    friend class List<T>;
    friend class ListIterator<T>;

  public:
    ListNode(const T &value, std::shared_ptr<ListNode<T>> next);

    T getValue() const;
    T &getValueRef();
    const T &getValueRef() const;

  private:
    T value;

    std::shared_ptr<ListNode<T>> next;
};

#include <list/ListNodeImpl.hpp>
