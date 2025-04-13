#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapIter.hpp"
#include "hashmap/HashMapNode.hpp"
#include <optional>

template <HashAndEqual K, typename V>
class HashMap : public BaseCollection
{
    friend class HashMapIterator<K, V>;
    friend class HashMapNode<K, V>;

  public:
    using key_type = K;
    using value_type = V;
    using iterator = HashMapIterator<K, V>;

    HashMap();
    explicit HashMap(const size_t initialSize);

    virtual ~HashMap() = default;

    void insert(const K &key, const V &value);

    std::optional<V> find(const K &key);

    bool contains(const K &key);

    void remove(const K &key);

    HashMapIterator<K, V> begin() const;
    HashMapIterator<K, V> end() const;

  private:
    size_t getEffectiveIndex(const K &key);

    void rebuild();

    size_t getNextPrime();

    float calculateLoadFactor();

    void resize(size_t newSize);

    size_t keyHash(const K &key);

    std::shared_ptr<HashMapNode<K, V>> lastNode;
    std::shared_ptr<HashMapNode<K, V>> firstNode;
    std::shared_ptr<HashMapNode<K, V>> sentinelNode;

    std::vector<std::shared_ptr<HashMapNode<K, V>>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
