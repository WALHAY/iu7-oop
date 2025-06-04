#include <QDebug>
#include <visitors/DrawVisitor.hpp>
#include <wireframe/Edge.hpp>

DrawVisitor::DrawVisitor(std::shared_ptr<GraphicsFactory> factory, std::shared_ptr<Canvas> canvas,
                         std::shared_ptr<Camera> camera)
    : graphicsFactory(factory), canvas(canvas), camera(camera)
{
}

void DrawVisitor::visit(Model &model)
{
	if(model.wireframeModel == nullptr)
	{
		return;
	}

    auto a = graphicsFactory->createPainter(canvas);

    for (const Edge &edge : model.wireframeModel->getEdges())
    {
        auto firstPoint = model.wireframeModel->getVertices().at(edge.getFirst());
        auto secondPoint = model.wireframeModel->getVertices().at(edge.getSecond());

        auto first = graphicsFactory->createPoint2D(firstPoint.getX(), firstPoint.getY());
        auto second = graphicsFactory->createPoint2D(secondPoint.getX(), secondPoint.getY());

        a->drawLine(first, second);
    }
}

void DrawVisitor::visit(Camera &camera)
{
}
