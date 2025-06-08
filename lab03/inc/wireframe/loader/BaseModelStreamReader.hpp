#pragma once

#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"

class BaseModelStreamReader
{
  public:
    virtual ~BaseModelStreamReader() = 0;

    virtual std::optional<Point> getPoint() = 0;
    virtual std::optional<Edge> getEdge() = 0;
};

inline BaseModelStreamReader::~BaseModelStreamReader() = default;
