#pragma once

#include "point.hpp"
#include <cstddef>

typedef struct {
	point3d_t *first;
	point3d_t *second;
} edge_t;

typedef struct {
	size_t edge_count;
	edge_t *edges;
} edges_t;

edge_t edge_init(point3d_t *first, point3d_t *second);

int draw_edge(const edge_t &edge);

int draw_edges(const edges_t &edges);
