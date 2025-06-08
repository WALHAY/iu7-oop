#pragma once

#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"

class BaseStreamReader
{
  public:
    virtual ~BaseStreamReader() = 0;

    virtual std::optional<Point> getPoint() = 0;
    virtual std::optional<Edge> getEdge() = 0;
};

inline BaseStreamReader::~BaseStreamReader() = default;
