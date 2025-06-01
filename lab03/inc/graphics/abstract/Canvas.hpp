#pragma once

#include <any>
class Canvas
{
  public:
    virtual ~Canvas() = 0;

    virtual int width() = 0;
    virtual int height() = 0;

    virtual std::any canvas() = 0;
};

inline Canvas::~Canvas() = default;
