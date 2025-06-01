#include <QGraphicsScene>
#include <graphics/qt/QtGraphics.hpp>

QtGraphics::QtGraphics(const std::shared_ptr<QGraphicsScene> &scene) : scene(scene)
{
}

void QtGraphics::displayCanvas(std::shared_ptr<Canvas> canvas)
{
    auto qtCanvas = std::any_cast<std::shared_ptr<QImage>>(canvas->canvas());
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*qtCanvas));
}
