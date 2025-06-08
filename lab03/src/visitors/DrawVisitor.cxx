#include "objects/impl/PlainCamera.hpp"
#include "visitors/ProjectionVisitor.hpp"
#include <QDebug>
#include <visitors/DrawVisitor.hpp>
#include <wireframe/Edge.hpp>

DrawVisitor::DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas,
                         std::shared_ptr<Camera> camera)
    : graphicsFactory(factory), canvas(canvas), camera(camera)
{
}

void DrawVisitor::visit(WireframeModel &model)
{
    if (model.wireframe == nullptr)
    {
        return;
    }

    auto painter = graphicsFactory->createPainter(canvas);

	auto impl = model.wireframe;
    auto edges = impl->getEdges();
    auto points = impl->getVertices();

    std::vector<Point> projected;

    for (const auto &p : points)
    {
        auto clone = p.clone();
        camera->accept(std::make_shared<ProjectionVisitor>(clone));
        projected.push_back(clone);
    }

    for (const auto &edge : edges)
    {
        auto p1 = projected[edge.getFirst()];
        auto p2 = projected[edge.getSecond()];

        if (p1.getZ() <= 1 || p2.getZ() <= 1)
            continue;

		auto gp1 = graphicsFactory->createPoint2D(p1.getX(), p1.getY());
		auto gp2 = graphicsFactory->createPoint2D(p2.getX(), p2.getY());

        painter->drawLine(gp1, gp2);
    }
}

void DrawVisitor::visit(PlainCamera &camera)
{
}
