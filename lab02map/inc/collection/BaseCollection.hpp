#pragma once

#include <cstddef>

class BaseCollection
{
  public:
    using size_type = std::size_t;

    BaseCollection();

    virtual ~BaseCollection() = 0;

    bool isEmpty() const;

    virtual size_t getSize() const = 0;

    virtual void clear() = 0;
};
