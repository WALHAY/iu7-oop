#pragma once

#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <memory.h>
#include "defines.h"
#include "geometry.h"

typedef struct {
	size_t start;
	size_t end;
} edge_t;

typedef struct {
	size_t edge_count;
	 edge_t *edges;
	point3d_t vertices[];
} figure_t;

int create_cube(figure_t** cube);

int create_pyramid(figure_t** cube);

int draw_figure(SDL_Renderer* renderer, const figure_t *figure);
