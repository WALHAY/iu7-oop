#pragma once

#include <QGraphicsScene>
#include <graphics/abstract/Graphics.hpp>

class QtGraphics : public Graphics
{
  public:
    QtGraphics(const std::shared_ptr<QGraphicsScene> scene);

    void displayCanvas(std::shared_ptr<Canvas> canvas) override;

  private:
    std::shared_ptr<QGraphicsScene> scene;
};
