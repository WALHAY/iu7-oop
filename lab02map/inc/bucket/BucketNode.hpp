#pragma once

#include "bucket/BucketConcepts.hpp"
#include <memory>

template <typename K, typename V>
    requires HashAndEqual<K>
class BucketNode final
{
  public:
    BucketNode(const K key, const V value);

    BucketNode(const BucketNode &other);
    BucketNode(BucketNode &&other);

    BucketNode &operator=(const BucketNode &other);
    BucketNode &operator=(BucketNode &&other);

    void setNext(const std::shared_ptr<BucketNode<K, V>> next);

    std::shared_ptr<BucketNode<K, V>> getNext() const;

    bool hasNext() const;

    K &getKey();
    V &getValue();

  private:
    std::shared_ptr<BucketNode<K, V>> next;

    K key;
    V value;
};

#include <bucket/BucketNodeImpl.hpp>
