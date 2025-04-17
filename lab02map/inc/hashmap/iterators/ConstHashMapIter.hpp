#pragma once

#include "list/List.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, MoveAndCopy V, typename Hash>
class HashMap;

template <typename K, typename V>
class ConstHashMapIterator : public BaseIterator
{
  public:
    using iterator_category = std::forward_iterator_tag;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = const std::pair<const K, V>;
    using const_value_type = const std::pair<const K, V>;
    using const_pointer = const_value_type *;
    using const_reference = const_value_type &;
    using local_iterator = List<value_type>::const_iterator;
    using iterator = ConstHashMapIterator<K, V>;
	using buckets_iterator = List<List<value_type>>::const_iterator;

    ConstHashMapIterator();
    ConstHashMapIterator(const buckets_iterator &current, const buckets_iterator &end);
    ConstHashMapIterator(const buckets_iterator &current, const buckets_iterator &end, const local_iterator &element);

	operator bool () const;

    const_pointer operator->() const;
    const_reference operator*() const;

    ConstHashMapIterator<K, V> &operator=(const ConstHashMapIterator<K, V> &other);

    ConstHashMapIterator<K, V> &operator++();
    ConstHashMapIterator<K, V> operator++(int);
	ConstHashMapIterator<K, V> operator+(size_type offset) const;
	ConstHashMapIterator<K, V> &operator+=(size_type offset);

    bool operator==(const ConstHashMapIterator<K, V> &iterator) const;
    bool operator!=(const ConstHashMapIterator<K, V> &iterator) const;

  protected:
	void moveNextBucket();
    std::weak_ptr<List<List<value_type>>> bucketsPtr;

    local_iterator elementIterator;
	buckets_iterator currentBucket;
	buckets_iterator endBucket;
};

#include <hashmap/iterators/ConstHashMapIterImpl.hpp>
