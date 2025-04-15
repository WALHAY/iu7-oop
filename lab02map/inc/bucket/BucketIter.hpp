#pragma once

#include "bucket/BucketNode.hpp"
#include "collection/BaseIterator.hpp"
#include <cstddef>
#include <iterator>

template <typename T>
class Bucket;

template <typename T>
class BucketIterator : public BaseIterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;
    using iterator = BucketIterator<T>;
    using pointer = T *;
    using reference = T &;

  public:
    BucketIterator();
    BucketIterator(const Bucket<T> &bucket);
    BucketIterator(const BucketIterator<T> &iterator);
    BucketIterator(const std::weak_ptr<BucketNode<T>> &node);

    operator bool();

    const T &operator*() const;
    reference operator*();
    const pointer operator->() const;
    pointer operator->();

    BucketIterator<T> operator+(size_type offset) const;
    BucketIterator<T> &operator++();
    BucketIterator<T> operator++(int);
    BucketIterator<T> &operator+=(size_type offset);

    BucketIterator<T> &operator=(const BucketIterator<T> &other);

    bool operator==(const BucketIterator<T> &other) const;
    bool operator!=(const BucketIterator<T> &other) const;

    bool isValid() const;

  private:
    void validatePtr(int line) const;

    std::weak_ptr<BucketNode<T>> nodePtr;

    T getPtr() const;
};

#include <bucket/BucketIterImpl.hpp>
