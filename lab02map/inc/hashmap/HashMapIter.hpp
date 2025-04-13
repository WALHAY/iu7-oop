#pragma once

#include "collection/BaseIterator.hpp"
#include "hashmap/HashMapConcepts.hpp"

template <HashAndEqual K, typename V>
class HashMap;

template <typename K, typename V>
    requires HashAndEqual<K>
class Iterator : public BaseIterator<typename HashMap<K, V>::HashMapNode>
{
  public:
    Iterator();

  protected:
};
