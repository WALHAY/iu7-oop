#include "wireframe/Edge.hpp"
#include <loader/directors/ModelDirector.hpp>

ModelDirector::ModelDirector(std::shared_ptr<BaseBuilder> builder)
{
    this->builder = builder;
}

std::shared_ptr<Object> ModelDirector::create(std::shared_ptr<BaseStreamReader> reader)
{

    builder->build();

    std::optional<Point> point;
    while ((point = reader->getPoint()).has_value())
        builder->buildPoint(point.value());

    std::optional<Edge> edge;
    while ((edge = reader->getEdge()).has_value())
        builder->buildEdge(edge.value());

    return builder->get();
}
