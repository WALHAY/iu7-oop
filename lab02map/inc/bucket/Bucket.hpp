#pragma once

#include <bucket/BucketConcepts.hpp>
#include <bucket/BucketNode.hpp>
#include <collection/BaseCollection.hpp>
#include <optional>

template <typename K, typename V>
    requires HashAndEqual<K>
class Bucket : public BaseCollection
{
  public:
    Bucket();

	virtual ~Bucket() = default;

    void insert(K key, V value);

    bool contains(const K &key) const;

	std::optional<V> find(const K &key) const;

    void remove(const K &key);

  private:
    std::shared_ptr<BucketNode<K, V>> head;
};

#include <bucket/BucketImpl.hpp>
