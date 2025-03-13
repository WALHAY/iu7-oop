#pragma once

#include "edges.hpp"
#include "point.hpp"
#include "vertices.hpp"

typedef struct figure_t
{
	point_t center;
	vertices_t vertices;
	edges_t edges;
} figure_t;

int figure_load(figure_t &figure, const char *figure_path);

void figure_move(figure_t &figure, const point_t &move);

void figure_rotate(figure_t &figure, const rotation_t &rotation);

void figure_scale(figure_t &figure, double scale);

int figure_draw(const graphics_t &graphics, const figure_t &figure);

void figure_destroy(figure_t &figure);
