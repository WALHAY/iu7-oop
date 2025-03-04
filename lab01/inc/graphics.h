#pragma once 

#include <stdbool.h>
#include "../inc/defines.h"
#include "vec3d.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>

typedef struct graphics_t graphics_t;

int graphics_init(graphics_t **graphics);

int graphics_draw_line(const graphics_t *graphics, const point3d_t *a, const point3d_t *b);

int graphics_set_color(const graphics_t *graphics, int r, int g, int b, int a);

int graphics_clear(const graphics_t *graphics);

int graphics_show(const graphics_t *graphics);

int graphics_delay(const graphics_t *graphics_t, int delay);

void graphics_destroy(graphics_t *graphics);
