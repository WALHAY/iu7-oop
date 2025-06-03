#pragma once

#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"
#include <vector>

class Wireframe
{
  public:
    Wireframe() = default;
    Wireframe(const Wireframe &wireframe) = default;
    Wireframe(std::vector<Point> &points, std::vector<Edge> &edges);

    void setVertices(std::vector<Point> &points);
    void setEdges(std::vector<Edge> &edges);

    std::vector<Point> &getVertices();
    std::vector<Edge> &getEdges();

	void transform(const Matrix<double> &transform);

  private:
    std::vector<Point> vertices;
    std::vector<Edge> edges;
};
