#include <graphics/qt/QtPoint2D.hpp>

QtPoint2D::QtPoint2D(int x, int y)
{
    point = QPoint(x, y);
}

int QtPoint2D::x()
{
    return point.x();
}

int QtPoint2D::y()
{
    return point.y();
}
