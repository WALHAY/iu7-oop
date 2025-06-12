#pragma once

#include "wireframe/Point.hpp"

class BaseCameraImpl
{
  public:
	virtual ~BaseCameraImpl() = 0;

    virtual Point getLocation() = 0;
    virtual void setLocation(const Point &location) = 0;

    virtual Point getForward() = 0;
    virtual Point getUp() = 0;
    virtual Point getRight() = 0;
    virtual void setForward(const Point &location) = 0;
    virtual void setUp(const Point &location) = 0;
    virtual void setRight(const Point &location) = 0;

    virtual void transform(const Matrix<double> &transform) = 0;
};

inline BaseCameraImpl::~BaseCameraImpl() = default;
