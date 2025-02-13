#pragma once

#include <SDL2/SDL.h>
#include "defines.h"

int init_sdl();

int create_window_and_renderer(SDL_Window **window, SDL_Renderer **renderer);
