#pragma once

#include "abstract/Canvas.hpp"
#include "abstract/Graphics.hpp"
#include "abstract/Painter.hpp"
#include "abstract/Point2D.hpp"

#include <memory>
class GraphicsFactory
{
  public:
    virtual ~GraphicsFactory() = 0;

    virtual std::shared_ptr<Canvas> createCanvas(int width, int height) = 0;
    virtual std::shared_ptr<Point2D> createPoint2D(int x, int y) = 0;
    virtual std::shared_ptr<Painter> createPainter(std::shared_ptr<Canvas> canvas) = 0;
    virtual std::shared_ptr<Graphics> getGraphics() = 0;

  protected:
    std::shared_ptr<Graphics> graphics;
};

inline GraphicsFactory::~GraphicsFactory() = default;
