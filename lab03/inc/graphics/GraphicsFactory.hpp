#pragma once

#include "abstract/Canvas.hpp"
#include "abstract/Point2D.hpp"
#include "abstract/Painter.hpp"
#include "abstract/Graphics.hpp"

#include <memory>
class GraphicsFactory
{
  public:
    virtual ~GraphicsFactory() = 0;

    virtual std::shared_ptr<Canvas> createCanvas(int, int);
    virtual std::shared_ptr<Point2D> createPoint2D(int, int);
    virtual std::shared_ptr<Painter> createPainter();
    virtual std::shared_ptr<Graphics> getGraphics();
};

inline GraphicsFactory::~GraphicsFactory() = default;
