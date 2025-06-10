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
    Point center = getCenter();
    for (auto &point : vertices)
    {
        Matrix<double> moveMatrix = Matrix<double>::identity(4);
        moveMatrix[3][0] = -center.getX();
        moveMatrix[3][1] = -center.getY();
        moveMatrix[3][2] = -center.getZ();

        point.transform(moveMatrix);

        point.transform(matrix);

        moveMatrix[3][0] = center.getX();
        moveMatrix[3][1] = center.getY();
        moveMatrix[3][2] = center.getZ();
        point.transform(moveMatrix);
    }
}

Point Wireframe::getCenter() const
{
    Point center(0, 0, 0);
    for (const Point &p : vertices)
    {
        center.setX(center.getX() + p.getX());
        center.setY(center.getY() + p.getY());
        center.setZ(center.getZ() + p.getZ());
    }

    center.setX(center.getX() / vertices.size());
    center.setY(center.getY() / vertices.size());
    center.setZ(center.getZ() / vertices.size());

    return center;
}
