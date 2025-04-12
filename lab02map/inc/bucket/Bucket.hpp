#pragma once

#include <collection/BaseCollection.hpp>
#include <bucket/BucketConcepts.hpp>

template<typename U, typename T>
class Bucket : public BaseCollection<T> {

  public:
    Bucket(const Bucket &other) = default;
    Bucket(Bucket &&other) = default;

    Bucket &operator=(const Bucket &other) = default;
    Bucket &operator=(Bucket &&other) = default;

	T getValue(U key);

	void removeValue(U key);

};
