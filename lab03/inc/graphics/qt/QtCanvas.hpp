#pragma once

#include <QImage>
#include <graphics/abstract/Canvas.hpp>

class QtCanvas : public Canvas
{
  public:
    QtCanvas(int width, int height);

    int width() override;
    int height() override;

    std::any canvas() override;

  private:
    std::shared_ptr<QImage> image;
};
