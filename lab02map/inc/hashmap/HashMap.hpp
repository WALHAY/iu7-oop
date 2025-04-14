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
    using value_type = V;
    using iterator = HashMapIterator<K, V>;
    using const_iterator = HashMapIterator<K, V>;

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
    void insert(const K &key, const V &value);
    template <Container C>
    void insertAll(const C &container);

    iterator find(const K &key);
    const_iterator find(const K &key) const;

    bool contains(const K &key) const;

    void remove(const K &key);
    void remove(K &&key);
    void remove(iterator pos);

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
    HashMapIterator<K, V> begin() const;
    HashMapIterator<K, V> end() const;

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

    void insertIntoBuckets(std::shared_ptr<std::shared_ptr<HashMapNode<K, V>>[]> buckets, const K &key, const V &value);

    float loadFactorThreshold = 1.0f;

    std::shared_ptr<HashMapNode<K, V>> lastNode;
    std::shared_ptr<HashMapNode<K, V>> firstNode;
    std::shared_ptr<HashMapNode<K, V>> sentinelNode;

    std::shared_ptr<std::shared_ptr<HashMapNode<K, V>>[]> buckets;
    size_t bucketCount;
};

#include <hashmap/HashMapImpl.hpp>
