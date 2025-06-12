#pragma once

#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"
#include <vector>

class BaseWireframe
{
  public:
	virtual ~BaseWireframe() = 0;

    virtual void setVertices(std::vector<Point> &points) = 0;
    virtual void setEdges(std::vector<Edge> &edges) = 0;

    virtual std::vector<Point> &getVertices() = 0;
    virtual std::vector<Edge> &getEdges() = 0;

    virtual Point getCenter() const = 0;

    virtual void transform(const Matrix<double> &transform) = 0;
};

inline BaseWireframe::~BaseWireframe() = default;
