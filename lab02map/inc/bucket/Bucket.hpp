#pragma once

#include <collection/BaseCollection.hpp>

template<typename T>
class Bucket : public BaseCollection<T> {

  public:
    Bucket(const Bucket &other) = default;
    Bucket(Bucket &&other) = default;

    Bucket &operator=(const Bucket &other) = default;
    Bucket &operator=(Bucket &&other) = default;

  private:
};
