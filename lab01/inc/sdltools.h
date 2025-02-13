#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include "geometry.h"
#include "graphics.h"
#include "defines.h"

int init_sdl();

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer);

int draw_loop(SDL_Renderer *renderer, const figure_t *figure);

void destroy_sdl(SDL_Window *window, SDL_Renderer *renderer);
