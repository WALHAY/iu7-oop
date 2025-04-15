#pragma once

#include <bucket/BucketNode.hpp>
#include <bucket/iterators/BucketIter.hpp>
#include <collection/BaseCollection.hpp>

template <typename T>
class Bucket
{
    friend class BucketNode<T>;

    using iterator = BucketIterator<T>;
    using value_type = T;
    using referece = T &;
    using pointer = T *;

  public:
    Bucket();

    void insertHead(const T &value);
    void insertTail(const T &value);

    /*
     * ITERATORS
     */
    iterator begin();
    iterator end();

  protected:
    std::shared_ptr<BucketNode<T>> head;
};

#include <bucket/BucketImpl.hpp>
