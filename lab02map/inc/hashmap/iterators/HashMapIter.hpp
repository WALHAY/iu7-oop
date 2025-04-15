#pragma once

#include "bucket/Bucket.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, MoveAndCopy V>
class HashMap;

template <typename K, typename V>
class HashMapIterator
{
    friend class HashMap<K, V>;

  public:
    using iterator_category = std::forward_iterator_tag;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = HashMap<K, V>::value_type;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = HashMapIterator<K, V>;

    HashMapIterator();
    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const HashMap<K, V> &map, size_type bucket);
    HashMapIterator(HashMapIterator<K, V> &&map) = default;
    HashMapIterator(const HashMapIterator<K, V> &map) = default;

    // pointer operator->();
    // const_pointer operator->() const;
    // reference operator*();
    // const_reference operator*() const;

    HashMapIterator<K, V> &operator++();
    HashMapIterator<K, V> operator++(int);

    bool operator==(const HashMapIterator<K, V> &iterator) const;
    bool operator!=(const HashMapIterator<K, V> &iterator) const;

    size_type findNextBucket();

  protected:
    std::weak_ptr<Bucket<value_type>[]> bucketsPtr;

    size_type bucketIndex;
    size_type bucketCount;
    HashMap<K, V>::local_iterator localIterator;
};

#include <hashmap/iterators/HashMapIterImpl.hpp>
