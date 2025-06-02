#pragma once

#include <QPainter>
#include <graphics/abstract/Canvas.hpp>
#include <graphics/abstract/Painter.hpp>

class QtPainter : public Painter
{
  public:
    QtPainter(std::shared_ptr<Canvas> canvas);

    void drawLine(std::shared_ptr<Point2D> first, std::shared_ptr<Point2D> second) override;

  private:
    std::shared_ptr<QPainter> painter;
};
