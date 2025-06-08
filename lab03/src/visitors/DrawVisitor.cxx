#include "objects/impl/PlainCamera.hpp"
#include <QDebug>
#include <visitors/DrawVisitor.hpp>
#include <wireframe/Edge.hpp>

DrawVisitor::DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas,
                         std::shared_ptr<PlainCamera> camera)
    : graphicsFactory(factory), canvas(canvas), camera(camera)
{
}

void DrawVisitor::visit(WireframeModel &model)
{
    if (model.wireframe == nullptr)
    {
        return;
    }

    auto a = graphicsFactory->createPainter(canvas);

    for (const Edge &edge : model.wireframe->getEdges())
    {
        auto firstPoint = model.wireframe->getVertices().at(edge.getFirst());
        auto secondPoint = model.wireframe->getVertices().at(edge.getSecond());

        auto first = graphicsFactory->createPoint2D(firstPoint.getX(), firstPoint.getY());
        auto second = graphicsFactory->createPoint2D(secondPoint.getX(), secondPoint.getY());

        a->drawLine(first, second);
    }
}

void DrawVisitor::visit(PlainCamera &camera)
{
}
