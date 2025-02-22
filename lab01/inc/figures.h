#pragma once

#include "defines.h"
#include "figure_state.h"
#include "geometry.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <memory.h>
#include <stdlib.h>

typedef struct
{
    size_t start;
    size_t end;
} edge_t;

typedef struct
{
    size_t edge_count;
    size_t vertex_count;
    edge_t *edges;
    point3d_t vertices[];
} figure_t;

int load_figure(FILE *file, figure_t **figure);

int draw_figure(const graphics_t *graphics, const figure_state_t *state, const figure_t *figure);

void free_figure(figure_t *figure);
