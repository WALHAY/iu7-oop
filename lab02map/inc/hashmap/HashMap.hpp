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

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(const size_t initialSize);
	HashMap(HashMapIterator<K, V>&& begin, HashMapIterator<K, V> &&end);
	HashMap(HashMap<K, V> &&map);
	HashMap(const HashMap<K, V> &map);

    virtual ~HashMap() = default;

    /*
     * DEFAULT OPERATIONS
     */
    void insert(const K &key, const V &value);
    HashMapIterator<K, V> find(const K &key) const;
    bool contains(const K &key) const;
    void remove(const K &key);

    void clear();

    /*
     * ITERATORS
     */
    HashMapIterator<K, V> begin() const;
    HashMapIterator<K, V> end() const;

  private:
    /*
     * REBUILD
     */
    void rebuild();
    float getLoadFactor() const;
    void resize(size_t newSize);
    size_t getNextPrime() const;

    size_t keyHash(const K &key) const;
    size_t getEffectiveIndex(const K &key) const;

    float loadFactorThreshold = 1.0f;

    std::shared_ptr<HashMapNode<K, V>> lastNode;
    std::shared_ptr<HashMapNode<K, V>> firstNode;
    std::shared_ptr<HashMapNode<K, V>> sentinelNode;

    std::vector<std::shared_ptr<HashMapNode<K, V>>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
