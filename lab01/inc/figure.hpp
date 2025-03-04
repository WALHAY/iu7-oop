#pragma once

#include "defines.hpp"
#include "graphics.hpp"
#include "point.hpp"
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

int figure_load(figure_t **figure, const char *figure_path);

void figure_draw(const graphics_t &graphics, const figure_t &figure);

void figure_move(figure_t &figure, const point3d_t &offset);

void figure_rotate(figure_t &figure, const point3d_t &center, const rotation3d_t &rotation);

void figure_scale(figure_t &figure, const point3d_t &center, double scale);

void figure_free(figure_t &figure);
