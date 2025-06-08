#include "objects/impl/WireframeModel.hpp"
#include <memory>
#include <wireframe/loader/builders/ModelBuilder.hpp>

void ModelBuilder::build()
{
    this->wireframe = std::make_shared<Wireframe>();
}

void ModelBuilder::buildEdge(const Edge &edge)
{
    if (wireframe == nullptr)
        return;

    this->wireframe->getEdges().push_back(edge);
}

void ModelBuilder::buildPoint(const Point &point)
{
    if (wireframe == nullptr)
        return;

    this->wireframe->getVertices().push_back(point);
}

bool ModelBuilder::validateBuild()
{
    if (wireframe == nullptr)
        return false;

	if(wireframe->getEdges().empty())
		return false;

	if(wireframe->getVertices().empty())
		return false;

    auto size = wireframe->getVertices().size();

    return std::ranges::none_of(wireframe->getEdges(), [size](const Edge &edge) {
        return std::max(edge.getFirst(), edge.getSecond()) >= size;
    });
}

std::shared_ptr<Object> ModelBuilder::get()
{
    if (!validateBuild())
        throw std::exception();

    return std::make_shared<WireframeModel>(wireframe);
}
