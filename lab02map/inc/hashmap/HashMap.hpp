#pragma once

#include "collection/BaseCollection.hpp"
#include "hashmap/HashMapConcepts.hpp"
#include "hashmap/HashMapIter.hpp"
#include <memory>
#include <optional>

template <HashAndEqual K, typename V>
class HashMap : public BaseCollection
{
    friend class Iterator<K, V>;

  public:
    class HashMapNode
    {
		friend class HashMap<K, V>;
      public:
        HashMapNode(K key, V value, std::shared_ptr<HashMapNode> next, std::shared_ptr<HashMapNode> previousInOrder,
                    std::shared_ptr<HashMapNode> nextInOrder, size_t hash);

        K key;
        V value;

		std::shared_ptr<HashMapNode> getNext();
		std::shared_ptr<HashMapNode> getPrevious();

      private:
        std::shared_ptr<HashMapNode> next;
        std::shared_ptr<HashMapNode> previousInOrder;
        std::shared_ptr<HashMapNode> nextInOrder;

        size_t hash;
    };

    HashMap();
    explicit HashMap(const size_t initialSize);

    virtual ~HashMap() = default;

    void insert(const K &key, const V &value);

    std::optional<V> find(const K &key);

    bool contains(const K &key);

    void remove(const K &key);

    Iterator<K, V> begin();
    Iterator<K, V> end();

  private:
    size_t getEffectiveIndex(const K &key);

    void rebuild();

    size_t getNextPrime();

    float calculateLoadFactor();

    void resize(size_t newSize);

    size_t keyHash(const K &key);

    std::shared_ptr<HashMapNode> lastNode;
    std::shared_ptr<HashMapNode> firstNode;
    std::vector<std::shared_ptr<HashMapNode>> buckets;
};

#include <hashmap/HashMapImpl.hpp>
