#pragma once

#include "Point2D.hpp"
#include <memory>

class Painter
{
  public:
    virtual ~Painter() = 0;

    virtual void drawLine(std::shared_ptr<Point2D> first, std::shared_ptr<Point2D> second) = 0;
};

inline Painter::~Painter() = default;
