#pragma once

#include "abstract/Canvas.hpp"
#include "abstract/Graphics.hpp"
#include "abstract/Painter.hpp"
#include "abstract/Point2D.hpp"

#include <graphics/GraphicsFactory.hpp>
#include <QGraphicsScene>

#include <memory>

class QtGraphicsFactory : public GraphicsFactory
{
  public:
    QtGraphicsFactory(std::shared_ptr<QGraphicsScene> scene);
    virtual ~QtGraphicsFactory() = 0;

    std::shared_ptr<Canvas> createCanvas(int width, int height) override;
    std::shared_ptr<Point2D> createPoint2D(int x, int y) override;
    std::shared_ptr<Painter> createPainter(std::shared_ptr<Canvas> canvas) override;
    std::shared_ptr<Graphics> getGraphics() override;
};

inline QtGraphicsFactory::~QtGraphicsFactory() = default;
