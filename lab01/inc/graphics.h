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

int load_figure(FILE *file, figure_t **figure);

void scale_figure(figure_t *figure, double scale);

int draw_figure(SDL_Renderer *renderer, const figure_t *figure, double rotx, double roty);
