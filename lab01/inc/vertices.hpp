#pragma once

#include "point.hpp"
#include <cstddef>
#include <cstdio>

typedef struct {
	size_t count;
	point3d_t *vertices;
} vertices_t;

int vertices_load(vertices_t &vertices, FILE *file);
