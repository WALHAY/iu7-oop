#include <QDebug>
#include <visitor/DrawVisitor.hpp>

DrawVisitor::DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas, std::shared_ptr<Camera> camera)
    : graphicsFactory(factory), canvas(canvas), camera(camera)
{
}

void DrawVisitor::visit(Composite &composite)
{
    auto a = graphicsFactory->createPainter(canvas);

    auto first = graphicsFactory->createPoint2D(10, 10);
    auto second = graphicsFactory->createPoint2D(300, 300);

    a->drawLine(first, second);
    qDebug() << "Composite visited";
}

void DrawVisitor::visit(Camera &camera)
{
    qDebug() << "Camera visited";
}
