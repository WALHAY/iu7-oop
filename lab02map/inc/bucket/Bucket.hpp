#pragma once

#include <bucket/BucketNode.hpp>
#include <bucket/iterators/BucketIter.hpp>
#include <collection/BaseCollection.hpp>

template <typename T>
class Bucket
{
  public:
    friend class BucketNode<T>;

    using iterator = BucketIterator<T>;
    using const_iterator = const BucketIterator<T>;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

    Bucket();

    void insertHead(const T &value);
    void insertTail(const T &value);

	void removeHead();
	void removeTail();

	iterator erase(const_iterator pos);

	reference getHead();
	const_reference getHead() const;

	reference getTail();
	const_reference getTail() const;

	void merge(Bucket &&bucket);
	void merge(const Bucket &bucket);
	
	bool isEmpty() const;

    /*
     * ITERATORS
     */
    iterator begin();
    iterator end();

  protected:
    std::shared_ptr<BucketNode<T>> head;
};

#include <bucket/BucketImpl.hpp>
