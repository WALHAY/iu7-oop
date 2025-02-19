#pragma once

#include "defines.h"
#include "figure_state.h"
#include "figures.h"
#include "geometry.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

int init_sdl();

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer);

int draw_loop(SDL_Renderer *renderer, const figure_t *figure, figure_state_t *state);

void destroy_sdl(SDL_Window *window, SDL_Renderer *renderer);
