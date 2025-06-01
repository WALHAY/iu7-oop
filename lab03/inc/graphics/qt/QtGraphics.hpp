#pragma once

#include <graphics/abstract/Graphics.hpp>
#include <QGraphicsScene>

class QtGraphics : public Graphics
{
  public:
	QtGraphics(const std::shared_ptr<QGraphicsScene> &scene);

	void displayCanvas(std::shared_ptr<Canvas> canvas) override;
  private:
	std::shared_ptr<QGraphicsScene> scene;
};
