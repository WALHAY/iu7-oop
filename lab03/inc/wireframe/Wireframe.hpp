#pragma once

#include "wireframe/BaseWireframe.hpp"
#include "wireframe/Edge.hpp"
#include "wireframe/Point.hpp"
#include <vector>

class Wireframe : public BaseWireframe
{
  public:
	Wireframe() = default;
    Wireframe(std::vector<Point> &points, std::vector<Edge> &edges);

    void setVertices(std::vector<Point> &points) override;
    void setEdges(std::vector<Edge> &edges) override;

    std::vector<Point> &getVertices() override;
    std::vector<Edge> &getEdges() override;

	Point getCenter() const override;

    void transform(const Matrix<double> &transform) override;

  private:
    std::vector<Point> vertices;
    std::vector<Edge> edges;
};
