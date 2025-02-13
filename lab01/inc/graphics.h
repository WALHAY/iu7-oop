#pragma once

#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <memory.h>
#include "defines.h"
#include "geometry.h"

typedef struct {
	size_t vertex_count;
	point3d_t vertices[];
} figure_t;

int create_cube(figure_t** cube);

int draw_figure(SDL_Renderer* renderer, const figure_t *figure);
