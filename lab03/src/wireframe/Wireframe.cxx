#include <wireframe/Wireframe.hpp>

Wireframe::Wireframe(std::vector<Point> &points, std::vector<Edge> &edges) : vertices(points), edges(edges)
{
}

void Wireframe::setVertices(std::vector<Point> &points)
{
    this->vertices = points;
}
void Wireframe::setEdges(std::vector<Edge> &edges)
{
    this->edges = edges;
}

std::vector<Point> &Wireframe::getVertices()
{
    return vertices;
}

std::vector<Edge> &Wireframe::getEdges()
{
    return edges;
}

void Wireframe::transform(const Matrix<double> &matrix)
{
    for (auto &point : vertices)
        point.transform(matrix);
}
