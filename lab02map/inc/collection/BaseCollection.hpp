#pragma once

#include <cstddef>

class BaseCollection
{
  public:
    BaseCollection();

    virtual ~BaseCollection() = 0;

    bool isEmpty() const;

    size_t getSize() const;

  protected:
    size_t size;
};
