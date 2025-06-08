#pragma once

#include "wireframe/Point.hpp"

class CameraImpl
{
  public:
	CameraImpl(Point location);

    Point getLocation();

    Point getForward();
    Point getUp();
    Point getRight();

  private:
    Point location;

    Point forward{1, 0, 0};
    Point up{0, 1, 0};
    Point right{0, 0, 1};
};
