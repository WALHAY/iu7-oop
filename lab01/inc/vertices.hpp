#pragma once

#include "point.hpp"
#include <cstddef>
#include <cstdio>
#include "defines.hpp"
#include "point.hpp"
#include <cstdlib>

typedef struct vertices_t {
	size_t count;
	point_t *vertices;
} vertices_t;

int vertices_load(vertices_t &vertices, FILE *file);

void vertices_move(vertices_t &vertices, const point_t &offset);

void vertices_rotate(vertices_t &vertices, const point_t &center, const rotation_t &offset);

void vertices_scale(vertices_t &vertices, const point_t &center, double scale);

void vertices_destroy(vertices_t &vertices);
