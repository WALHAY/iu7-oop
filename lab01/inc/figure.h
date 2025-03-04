#pragma once

#include "defines.h"
#include "geometry.h"
#include "graphics.h"
#include "vec3d.h"
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

int figure_load(const char *figure_path, figure_t **figure);

int figure_draw(const graphics_t *graphics, figure_t *figure);

int figure_move(figure_t *figure, const point3d_t offset);

int figure_rotate(figure_t *figure, const point3d_t *center, const rotation3d_t *rotation);

int figure_scale(figure_t *figure, const point3d_t *center, double scale);

void figure_free(figure_t *figure);
