#pragma once

#include "bucket/BucketIter.hpp"
#include "collection/BaseCollection.hpp"
#include <memory>

template <typename T>
class Bucket : public BaseCollection
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
    std::shared_ptr<BucketNode<T>> sentinelNode;
};

#include <bucket/BucketImpl.hpp>
