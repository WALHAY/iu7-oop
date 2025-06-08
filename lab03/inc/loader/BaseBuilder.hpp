#pragma once

#include "objects/Object.hpp"
#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"

class BaseBuilder
{
  public:
    virtual ~BaseBuilder() = 0;

    virtual void build() = 0;

    virtual void buildDirection(const Point &point);
    virtual void buildPoint(const Point &point);
    virtual void buildEdge(const Edge &edge);

    virtual std::shared_ptr<Object> get() = 0;
};
