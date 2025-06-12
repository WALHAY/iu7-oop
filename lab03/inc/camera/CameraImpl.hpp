#pragma once

#include "camera/BaseCameraImpl.hpp"
#include "wireframe/Point.hpp"

class CameraImpl : public BaseCameraImpl
{
  public:
    CameraImpl(const Point &location);

    Point getLocation() override;
    void setLocation(const Point &location) override;

    Point getForward() override;
    Point getUp() override;
    Point getRight() override;
    void setForward(const Point &location) override;
    void setUp(const Point &location) override;
    void setRight(const Point &location) override;

    void transform(const Matrix<double> &transform) override;

  private:
    Point location;

    Point forward{0, 1, 0};
    Point up{0, 0, 1};
    Point right{1, 0, 0};
};
