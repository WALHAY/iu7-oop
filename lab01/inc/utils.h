#pragma once

#include <SDL2/SDL.h>
#include "defines.h"

int init_sdl();

int create_window_and_surface(SDL_Window** window, SDL_Surface **surface);
