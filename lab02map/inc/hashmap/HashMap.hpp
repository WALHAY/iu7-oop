#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/iterators/ConstHashMapIter.hpp"
#include "hashmap/iterators/HashMapIter.hpp"
#include "list/iterators/ListIter.hpp"

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash = std::hash<K>, EqualFunction<K> KeyEqual = std::equal_to<K>>
class HashMap : public BaseCollection
{
    friend class HashMapIterator<K, V>;

  public:
    using key_type = K;
    using mapped_type = V;
    using value_type = std::pair<const K, V>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
	using hasher = Hash;
	using key_equal = KeyEqual;
    using iterator = HashMapIterator<K, V>;
    using const_iterator = ConstHashMapIterator<K, V>;
    using local_iterator = List<value_type>::iterator;
    using const_local_iterator = List<value_type>::const_iterator;
	using hashmap = HashMap<K, V, Hash, KeyEqual>;

    /*
     * CONSTRUCTORS
     */
    HashMap();
    explicit HashMap(size_type size);
    HashMap(std::initializer_list<value_type> list);
    HashMap(hashmap &&map) = default;
    HashMap(const hashmap &map) = default;

    template <ConvertibleIterator<value_type> Iter>
    HashMap(Iter &&begin, Iter &&end);

    virtual ~HashMap() = default;

    /*
     * MODIFIERS
     */
    std::pair<iterator, bool> emplace(const K &key, const V &value);
    std::pair<iterator, bool> emplace(value_type entry);

    bool erase(const K &key);
    iterator erase(iterator pos);

    virtual void clear() override;

    /*
     * ITERATORS
     */
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

	/*
	 * LOOKUP
	 */
    V &at(const K &key);
    const V &at(const K &key) const;

    V &operator[](const K &key);
    const V &operator[](const K &key) const;

    iterator find(const K &key);
    const_iterator find(const K &key) const;

    bool contains(const K &key) const;
    bool contains(K &&key) const;

	/*
	 * BUCKET INTERFACE
	 */
    local_iterator begin(size_type bucket);
    local_iterator end(size_type bucket);
    const_local_iterator begin(size_type bucket) const;
    const_local_iterator end(size_type bucket) const;
    const_local_iterator cbegin(size_type bucket) const;
    const_local_iterator cend(size_type bucket) const;

    size_type getBucketCount() const;

	List<value_type>::size_type getBucketSize(size_type bucket) const;

    size_type getBucket(const K &key) const;

	/*
	 * HASH POLICY
	 */

    void setMaxLoadFactor(float maxLoadFactor) const;
    float getMaxLoadFactor() const;

	void rehash(size_type buckets);
	void reserve(size_type elements);

	/*
	 * OBSERVERS
	 */
	key_equal getKeyEqual() const;
	hasher getHashFunction() const;

    virtual size_type getSize() const override;

  private:
    /*
     * REBUILD
     */
    void rebuild();
    float countLoadFactor() const;

    bool isPrime(size_type value) const;
    size_type getNextPrime(size_type size) const;

    std::pair<iterator, bool> insert(List<List<value_type>> &buckets, value_type &entry);

    const float maxLoadFactor = 1.0f;
    const float sizeFactor = 1.5f;

    const Hash hashFunction;
	const KeyEqual keyEqualFunction;

    List<List<value_type>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
