#pragma once

#include "defines.h"
#include "geometry.h"
#include <SDL2/SDL.h>
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

point3d_t create_point(double x, double y, double z);

int load_figure(FILE *file, figure_t **figure);

int draw_figure(SDL_Renderer *renderer, const figure_t *figure, double scale, double posX, double posY, double rotX, double rotY);
