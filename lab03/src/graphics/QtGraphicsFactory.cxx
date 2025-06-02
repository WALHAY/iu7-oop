#include <graphics/QtGraphicsFactory.hpp>

#include <graphics/qt/QtCanvas.hpp>
#include <graphics/qt/QtGraphics.hpp>
#include <graphics/qt/QtPainter.hpp>
#include <graphics/qt/QtPoint2D.hpp>

QtGraphicsFactory::QtGraphicsFactory(std::shared_ptr<QGraphicsScene> scene) {
	graphics = std::make_shared<QtGraphics>(scene);
}

std::shared_ptr<Canvas> QtGraphicsFactory::createCanvas(int width, int height)
{
    return std::make_shared<QtCanvas>(width, height);
}

std::shared_ptr<Point2D> QtGraphicsFactory::createPoint2D(int x, int y)
{
    return std::make_shared<QtPoint2D>(x, y);
}

std::shared_ptr<Painter> QtGraphicsFactory::createPainter(std::shared_ptr<Canvas> canvas)
{
    return std::make_shared<QtPainter>(std::any_cast<std::shared_ptr<QImage>>(canvas->canvas()));
}

std::shared_ptr<Graphics> QtGraphicsFactory::getGraphics()
{
    return graphics;
}
