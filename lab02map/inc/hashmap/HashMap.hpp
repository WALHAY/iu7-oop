#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/iterators/ConstHashMapIter.hpp"
#include "hashmap/iterators/HashMapIter.hpp"
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
    using const_iterator = ConstHashMapIterator<K, V>;
    using node_type = HashMapNode<K, V>;

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(const size_t initialSize);
    HashMap(iterator &&begin, iterator &&end);
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
	const_iterator find(const K &key) const;

    bool contains(const K &key) const;
    bool contains(K&& key) const;

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
    const_iterator cbegin() const;
    const_iterator cend() const;

    size_t getBucketCount() const;

  private:
    /*
     * REBUILD
     */
    void rebuild();
    float countLoadFactor() const;

	bool isPrime(size_type value) const;
    size_t getNextPrime(size_type size) const;

	/*
	* KEYS & HASH
	*/
    size_t getKeyHash(const K &key) const;
    size_t getKeyIndex(const K &key) const;

    void fixRemovedHeadTail(std::shared_ptr<HashMapNode<K, V>> node);

    std::pair<iterator, bool> insert(std::vector<std::shared_ptr<HashMapNode<K, V>>> &buckets, const K &key,
                                     const V &value);

    const float loadFactorThreshold = 1.0f;
	const float sizeFactor = 1.5f;

    std::shared_ptr<HashMapNode<K, V>> lastNode;
    std::shared_ptr<HashMapNode<K, V>> firstNode;
    std::shared_ptr<HashMapNode<K, V>> sentinelNode;

    std::vector<std::shared_ptr<HashMapNode<K, V>>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
