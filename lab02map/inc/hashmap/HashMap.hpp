#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapIter.hpp"
#include "hashmap/HashMapNode.hpp"

template <HashAndEqual K, MoveAndCopy V>
class HashMap : public BaseCollection
{
    friend class HashMapIterator<K, V>;
    friend class HashMapNode<K, V>;

  public:
    using key_type = K;
    using mapped_type = V;
	using size_type = size_t;
	using difference_type = std::ptrdiff_t;
    using iterator = HashMapIterator<K, V>;
    using const_iterator = HashMapIterator<K, V>;
	using node_type = HashMapNode<K, V>;

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(const size_t initialSize);
    HashMap(iterator &&begin, iterator &&end);
    HashMap(HashMap<K, V> &&map) = default;
    explicit HashMap(const HashMap<K, V> &map) = default;

    virtual ~HashMap() = default;

    /*
     * DEFAULT OPERATIONS
     */
	std::pair<iterator, bool> emplace(const K &key, const V &value);
	std::pair<iterator, bool> emplace(std::pair<K, V> pair);

    iterator find(const K &key);
    iterator find(K &&key);

    bool contains(const K &key) const;

    iterator erase(const K &key);
    iterator erase(K &&key);
    iterator erase(iterator pos);

    void clear();

    /*
     * INDEX ACCESS
     */
    V &at(const K &key);
    const V &at(const K& key) const;

    V &operator[](const K &key);
    V &operator[](K &&key);

    /*
     * ITERATORS
     */
    iterator begin() const;
    iterator end() const;

    size_t getBucketCount();

  private:
    /*
     * REBUILD
     */
    void rebuild();
    float getLoadFactor() const;
    size_t getNextPrime(size_t size) const;

    size_t keyHash(const K &key) const;
    size_t getEffectiveIndex(const K &key) const;

    void fixRemovedHeadTail(std::shared_ptr<HashMapNode<K, V>> node);

    std::pair<iterator, bool> insertIntoBuckets(std::shared_ptr<std::shared_ptr<HashMapNode<K, V>>[]> buckets, const K &key, const V &value);

    float loadFactorThreshold = 1.0f;

    std::shared_ptr<HashMapNode<K, V>> lastNode;
    std::shared_ptr<HashMapNode<K, V>> firstNode;
    std::shared_ptr<HashMapNode<K, V>> sentinelNode;

    std::shared_ptr<std::shared_ptr<HashMapNode<K, V>>[]> buckets;
    size_t bucketCount;
};

#include <hashmap/HashMapImpl.hpp>
