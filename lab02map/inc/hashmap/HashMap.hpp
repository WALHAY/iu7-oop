#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/iterators/ConstHashMapIter.hpp"
#include "hashmap/iterators/HashMapIter.hpp"
#include "list/iterators/ListIter.hpp"

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash = std::hash<K>>
class HashMap : public BaseCollection
{
    friend class HashMapIterator<K, V>;

  public:
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const K, V>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = HashMapIterator<K, V>;
    using const_iterator = ConstHashMapIterator<K, V>;
    using local_iterator = List<value_type>::iterator;

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(size_type size);
    HashMap(const std::initializer_list<value_type> &list);
    HashMap(HashMap<K, V, Hash> &&map) = default;
    HashMap(const HashMap<K, V, Hash> &map) = default;

    template <ConvertibleIterator<value_type> Iter>
    HashMap(Iter &&begin, Iter &&end);

    virtual ~HashMap() = default;

    /*
     * DEFAULT OPERATIONS
     */
    std::pair<iterator, bool> emplace(const K &key, const V &value);
    std::pair<iterator, bool> emplace(value_type entry);

    iterator find(const K &key);
    const_iterator find(const K &key) const;

    bool contains(const K &key) const;
    bool contains(K &&key) const;

    bool erase(const K &key);
    iterator erase(iterator pos);

    virtual void clear() override;

    /*
     * KEY ACCESS
     */
    V &at(const K &key);
    const V &at(const K &key) const;

    V &operator[](const K &key);
    const V &operator[](const K &key) const;

    /*
     * ITERATORS
     */
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    local_iterator begin(size_type bucket);
    local_iterator end(size_type bucket);

    size_type getBucketCount() const;
    virtual size_type getSize() const override;

    void setMaxLoadFactor(float maxLoadFactor) const;
    float getMaxLoadFactor() const;

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

    std::pair<iterator, bool> insert(List<List<value_type>> &buckets, value_type &entry);

    const float maxLoadFactor = 1.0f;
    const float sizeFactor = 1.5f;

    const Hash hasher;

    List<List<value_type>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
