#pragma once

#include <cstddef>
#include <iterator>
#include <memory>

template <typename T>
class Bucket;

template <typename T>
class BucketNode;

template <typename T>
class BucketIterator
{
  public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = BucketIterator<T>;
    using iterator_category = std::forward_iterator_tag;

    BucketIterator();
    BucketIterator(const Bucket<T> &bucket);
    BucketIterator(const BucketIterator<T> &iterator);
    BucketIterator(const std::shared_ptr<BucketNode<T>> &node);

    reference operator*() const;
    pointer operator->() const;

    BucketIterator<T> &operator++();
    BucketIterator<T> operator++(int);

    BucketIterator<T> &operator=(const BucketIterator<T> &other);

    bool operator==(const BucketIterator<T> &other) const;
    bool operator!=(const BucketIterator<T> &other) const = default;

    bool isValid() const;

    operator bool() const;

  private:
    void validatePtr(int line) const;

    std::weak_ptr<BucketNode<T>> nodePtr;
};

#include <bucket/iterators/BucketIterImpl.hpp>
