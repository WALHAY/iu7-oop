#pragma once

#include "objects/Object.hpp"
#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"

class BaseModelBuilder
{
  public:
    virtual ~BaseModelBuilder() = 0;

    virtual void build() = 0;

    virtual void buildPoint(const Point &point) = 0;
    virtual void buildEdge(const Edge &edge) = 0;

    virtual std::shared_ptr<Object> get() = 0;
};

inline BaseModelBuilder::~BaseModelBuilder() = default;
