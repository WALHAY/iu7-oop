#pragma once

#include "point.hpp"
#include <cstddef>
#include <cstdio>

typedef struct {
	size_t count;
	point3d_t *vertices;
} vertices_t;

int vertices_load(vertices_t &vertices, FILE *file);

void vertices_move(vertices_t &vertices, const point3d_t &offset);

void vertices_rotate(vertices_t &vertices, const point3d_t &center, const point3d_t &offset);

void vertices_scale(vertices_t &vertices, const point3d_t &center, double scale);
