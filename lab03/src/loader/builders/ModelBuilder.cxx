#include "objects/Model.hpp"
#include <loader/builders/ModelBuilder.hpp>
#include <memory>

void ModelBuilder::build() {
	this->wireframe = std::make_shared<Wireframe>();
}

void ModelBuilder::buildEdge(const Edge &edge)
{
	if(wireframe == nullptr)
		return;
	this->wireframe->getEdges().push_back(edge);
}

void ModelBuilder::buildPoint(const Point &point)
{
	if(wireframe == nullptr)
		return;
	this->wireframe->getVertices().push_back(point);
}

std::shared_ptr<Object> ModelBuilder::get()
{
    return std::make_shared<Model>(wireframe);
}
