#pragma once

#include <bucket/BucketNode.hpp>
#include <collection/BaseCollection.hpp>
#include <bucket/BucketConcepts.hpp>

template<typename K, typename V>
	requires HashAndEqual<K>
class Bucket : public BaseCollection<BucketNode<K,V>> {

  public:
    Bucket(const Bucket &other) = default;
    Bucket(Bucket &&other) = default;

    Bucket &operator=(const Bucket &other) = default;
    Bucket &operator=(Bucket &&other) = default;

	bool contains(K &key) const;
	bool contains(BucketNode<K, V> bucket) const override;

	V& find(K& key);

	void removeValue(K key);
	void removeValue(BucketNode<K, V> node) override;

};
