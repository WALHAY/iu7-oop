#pragma once

#include "bucket/iterators/BucketIter.hpp"
#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/iterators/HashMapIter.hpp"
template <HashAndEqual K, MoveAndCopy V>

class HashMap : public BaseCollection
{
  public:
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const K, V>;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = HashMapIterator<K, V>;
    using local_iterator = BucketIterator<value_type>;

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(const size_type initialSize);
    // HashMap(iterator &&begin, iterator &&end);
    HashMap(const std::initializer_list<std::pair<K, V>> list);
    HashMap(HashMap<K, V> &&map) = default;
    explicit HashMap(const HashMap<K, V> &map) = default;

    virtual ~HashMap() = default;

    /*
     * DEFAULT OPERATIONS
     */
    std::pair<iterator, bool> emplace(const K &key, const V &value);
    std::pair<iterator, bool> emplace(std::pair<K, V> entry);

    iterator find(const K &key);
    // const_iterator find(const K &key) const;

    bool contains(const K &key) const;
    bool contains(K &&key) const;

    bool erase(const K &key);
    iterator erase(iterator pos);

    void clear();

    /*
     * KEY ACCESS
     */
    V &at(const K &key);
    const V &at(const K &key) const;

    V &operator[](const K &key);
    V &operator[](K &&key);

    /*
     * ITERATORS
     */
    iterator begin() const;
    iterator end() const;

	local_iterator begin(size_type bucket);
	local_iterator end(size_type bucket);

    size_type getBucketCount() const;

  private:
    /*
     * REBUILD
     */
    void rebuild();
    float countLoadFactor() const;

    bool isPrime(size_type value) const;
    size_type getNextPrime(size_type size) const;

    /*
     * KEYS & HASH
     */
    size_t getKeyHash(const K &key) const;
    size_type getBucket(const K &key) const;

    std::pair<iterator, bool> insert(std::shared_ptr<Bucket<value_type>[]> &buckets, const K &key, const V &value);

    const float loadFactorThreshold = 1.0f;
    const float sizeFactor = 1.5f;

    std::shared_ptr<Bucket<value_type>[]> buckets;
	size_type bucketCount;
};

#include <hashmap/HashMapImpl.hpp>
