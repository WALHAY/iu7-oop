#pragma once

#include "wireframe/Point.hpp"

class CameraImpl
{
  public:
    CameraImpl();
    CameraImpl(Point location);

    Point getLocation();
    void setLocation(const Point &location);

    Point getForward();
    Point getUp();
    Point getRight();
    void setForward(const Point &location);
    void setUp(const Point &location);
    void setRight(const Point &location);

  private:
    Point location;

    Point forward{1, 0, 0};
    Point up{0, 1, 0};
    Point right{0, 0, 1};
};
