#include <graphics/qt/QtCanvas.hpp>

QtCanvas::QtCanvas(int width, int height)
{
    image = std::make_shared<QImage>(width, height, QImage::Format_RGB32);
    image->fill(Qt::white);
}

int QtCanvas::width()
{
    return image->width();
}

int QtCanvas::height()
{
    return image->height();
}

std::any QtCanvas::canvas()
{
    return image;
}
