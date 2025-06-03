#pragma once

class Point2D
{
  public:
    virtual ~Point2D() = 0;

    virtual int x() = 0;
    virtual int y() = 0;
};

inline Point2D::~Point2D() = default;
