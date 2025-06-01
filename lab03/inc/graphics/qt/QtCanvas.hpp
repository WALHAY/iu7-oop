#pragma once

#include <graphics/abstract/Canvas.hpp>
#include <QImage>

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
