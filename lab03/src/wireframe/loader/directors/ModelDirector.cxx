#include "wireframe/Edge.hpp"
#include <wireframe/loader/directors/ModelDirector.hpp>

ModelDirector::ModelDirector(std::shared_ptr<BaseModelBuilder> builder) : BaseModelDirector(builder)
{
}

std::shared_ptr<Object> ModelDirector::create(std::shared_ptr<BaseModelStreamReader> reader)
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
