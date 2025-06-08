#pragma once

#include "objects/Object.hpp"
#include "wireframe/Point.hpp"
#include <memory>
class BaseCameraBuilder
{
  public:
    virtual ~BaseCameraBuilder() = 0;

    virtual void build() = 0;

    virtual void buildLocation(const Point &location) = 0;
    virtual void buildDirection(const Point &direction) = 0;

    virtual std::shared_ptr<Object> get() = 0;
};

inline BaseCameraBuilder::~BaseCameraBuilder() = default;
