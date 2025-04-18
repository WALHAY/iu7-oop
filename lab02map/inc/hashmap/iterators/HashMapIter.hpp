#pragma once

#include "list/List.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <EqualityComparable K, MoveAndCopy V, HashFunction<K> Hash, EqualFunction<K> KeyEqual>
class HashMap;

template <typename K, typename V>
class HashMapIterator : public BaseIterator
{
  public:
    using iterator_category = std::forward_iterator_tag;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const K, V>;
    using pointer = value_type *;
    using reference = value_type &;
    using local_iterator = List<value_type>::iterator;
    using iterator = HashMapIterator<K, V>;
	using buckets_iterator = List<List<value_type>>::iterator;

    HashMapIterator() = default;
    HashMapIterator(const buckets_iterator &current, const buckets_iterator &end);
    HashMapIterator(const buckets_iterator &current, const buckets_iterator &end, const local_iterator &element);

	operator bool () const;

    pointer operator->() const;
    reference operator*() const;

    HashMapIterator<K, V> &operator=(const HashMapIterator<K, V> &other);

    HashMapIterator<K, V> &operator++();
    HashMapIterator<K, V> operator++(int);
	HashMapIterator<K, V> operator+(size_type offset) const;
	HashMapIterator<K, V> &operator+=(size_type offset);

    bool operator==(const HashMapIterator<K, V> &iterator) const;

	bool isValid() const;

  protected:
	void validateIterator(int line) const;
	void moveNextBucket();

    local_iterator elementIterator;
	buckets_iterator currentBucket;
	buckets_iterator endBucket;
};

#include <hashmap/iterators/HashMapIterImpl.hpp>
