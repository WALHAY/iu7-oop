#pragma once

#include "list/List.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, MoveAndCopy V>
class HashMap;

template <typename K, typename V>
class HashMapIterator
{
    friend class HashMap<K, V>;
	friend class ListIterator<std::pair<const K, V>>;

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

    HashMapIterator();
    HashMapIterator(const HashMap<K, V> &map);
    HashMapIterator(const buckets_iterator &current, const buckets_iterator &end);
    HashMapIterator(const buckets_iterator &current, const buckets_iterator &end, const local_iterator &element);

	operator bool () const;

    pointer operator->() const;
    reference operator*() const;

    HashMapIterator<K, V> &operator=(const HashMapIterator<K, V> &other);

    HashMapIterator<K, V> &operator++();
    HashMapIterator<K, V> operator++(int);

    bool operator==(const HashMapIterator<K, V> &iterator) const;
    bool operator!=(const HashMapIterator<K, V> &iterator) const;

  protected:
    std::weak_ptr<List<List<value_type>>> bucketsPtr;

    local_iterator elementIterator;
	buckets_iterator currentBucket;
	buckets_iterator endBucket;
};

#include <hashmap/iterators/HashMapIterImpl.hpp>
