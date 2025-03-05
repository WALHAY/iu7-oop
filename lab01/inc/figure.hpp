#pragma once

#include "edges.hpp"
#include "point.hpp"
#include "vertices.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory.h>
#include <stdlib.h>

typedef struct
{
	point3d_t center;
	vertices_t vertices;
	edges_t edges;
} figure_t;

int figure_load(figure_t &figure, const char *figure_path);

void figure_move(figure_t &figure, const point3d_t &offset);

void figure_rotate(figure_t &figure, const rotation3d_t &rotation);

void figure_scale(figure_t &figure, double scale);

void figure_free(figure_t &figure);
