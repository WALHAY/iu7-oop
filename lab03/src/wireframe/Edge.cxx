#include <wireframe/Edge.hpp>

Edge::Edge(size_t first, size_t second) : first(first), second(second)
{
}

size_t Edge::getFirst()
{
    return first;
}

size_t Edge::getSecond()
{
    return second;
}

size_t Edge::getFirst() const
{
    return first;
}

size_t Edge::getSecond() const
{
    return second;
}
