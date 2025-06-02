#include <graphics/qt/QtPainter.hpp>

QtPainter::QtPainter(std::shared_ptr<Canvas> canvas)
{
    painter = std::make_shared<QPainter>();
}

void QtPainter::drawLine(std::shared_ptr<Point2D> first, std::shared_ptr<Point2D> second)
{
    painter->drawLine(first->x(), first->y(), second->x(), second->y());
}
