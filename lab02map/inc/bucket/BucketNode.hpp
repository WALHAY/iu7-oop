#pragma once

#include "bucket/BucketConcepts.hpp"
#include <memory>

template <typename Key, typename Value>
	requires HashAndEqual<Key>
class BucketNode final
{
  public:
    BucketNode(Key key, Value value);

    void setNext(std::shared_ptr<BucketNode<Key, Value>> next);

    std::shared_ptr<BucketNode<Key, Value>> getNext() const;

    bool hasNext() const;

	Key& getKey() const;
	Value& getValue() const;

  private:
    std::shared_ptr<BucketNode<Key, Value>> next;

	Key key;
	Value value;
};

#include <bucket/BucketNodeImpl.hpp>
