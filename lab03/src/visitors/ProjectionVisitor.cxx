#include "ui/RenderConfig.hpp"
#include <visitors/ProjectionVisitor.hpp>
#include <cmath>

ProjectionVisitor::ProjectionVisitor(Point &point) : point(point)
{
}

double dotProduct(const Point &p1, const Point &p2)
{
    return p1.getX() * p2.getX() + p1.getY() * p2.getY() + p1.getZ() * p2.getZ();
}

void ProjectionVisitor::visit(WireframeModel &model)
{
}

void ProjectionVisitor::visit(PlainCamera &camera)
{
    auto impl = camera.cameraImpl;
    auto copy = point.clone();

    Point relative = Point(copy.getX() - impl->getLocation().getX(), copy.getY() - impl->getLocation().getY(),
                           copy.getZ() - impl->getLocation().getZ());

    double xCam = dotProduct(relative, impl->getRight());
    double yCam = dotProduct(relative, impl->getUp());
    double zCam = dotProduct(relative, impl->getForward());

    copy.setZ(zCam);

    if (fabs(zCam) < __DBL_EPSILON__)
        zCam = 1e-6;

    double px = xCam / zCam;
    double py = yCam / zCam;

    double screen_x = (px + 1) * RenderWidth / 2;
    double screen_y = (1 - py) * RenderHeight / 2;

    copy.setX(screen_x);
    copy.setY(screen_y);

    point = copy;
}
