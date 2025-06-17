#include "wireframe/Edge.hpp"
#include <wireframe/loader/directors/ModelDirector.hpp>

ModelDirector::ModelDirector(std::shared_ptr<BaseModelBuilder> builder, std::shared_ptr<BaseModelStreamReader> reader)
{
	this->reader = reader;
    this->builder = builder;
}

std::shared_ptr<Object> ModelDirector::create()
{
    builder->build();

    std::optional<Point> point;
    while ((point = reader->getPoint()))
        builder->buildPoint(*point);

    std::optional<Edge> edge;
    while ((edge = reader->getEdge()))
        builder->buildEdge(*edge);

    return builder->get();
}
