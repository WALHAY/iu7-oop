#pragma once

#include "graphics.hpp"
#include "vertices.hpp"
#include "defines.hpp"
#include "point.hpp"
#include "projection.hpp"
#include <cstdlib>

typedef struct edge_t {
	const point3d_t *first;
	const point3d_t *second;
} edge_t;

typedef struct edges_t {
	size_t count;
	edge_t *edges;
} edges_t;

int edges_load(edges_t &edges, FILE *file, const vertices_t &vertices);

int edges_draw(const graphics_t &graphics, const edges_t &edges);

void edges_destroy(edges_t &edges);
