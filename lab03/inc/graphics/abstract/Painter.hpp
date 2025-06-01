#pragma once

#include "Point2D.hpp"

class Painter
{
  public:
    virtual ~Painter() = 0;

    virtual void drawLine(Point2D first, Point2D second);
};

inline Painter::~Painter() = default;
