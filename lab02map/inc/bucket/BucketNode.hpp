#pragma once

#include <memory>

template <typename T>
class Bucket;

template <typename T>
class BucketIterator;

template <typename T>
class BucketNode
{
    friend class Bucket<T>;
    friend class BucketIterator<T>;

  public:
    BucketNode(const T &value, std::shared_ptr<BucketNode<T>> next);

    T getValue() const;
    T &getValueRef();
    const T &getValueRef() const;

  private:
    T value;

    std::shared_ptr<BucketNode<T>> next;
};

#include <bucket/BucketNodeImpl.hpp>
