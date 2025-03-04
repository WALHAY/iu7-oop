#include "edges.hpp"

edge_t edge_init(point3d_t *first, point3d_t *second)
{
	edge_t edge;
	edge.first = first;
	edge.second = second;
	return edge;
}

int draw_edge(const edge_t &edge)
{
	return 0;
}

int draw_edges(const edges_t &edges)
{
	return 0;
}
