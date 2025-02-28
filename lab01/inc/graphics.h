#pragma once 

#include <stdbool.h>
#include "figure_state.h"
#include "../inc/defines.h"
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

bool graphics_quit_requested(int *rc, const graphics_t *graphics);

int graphics_event_handler(figure_state_t *state, const graphics_t *graphics);

bool graphics_valid(const graphics_t *graphics);

int graphics_delay(const graphics_t *graphics_t, int delay);

void graphics_destroy(graphics_t *graphics);
