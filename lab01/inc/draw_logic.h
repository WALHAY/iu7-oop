#pragma once

#include "graphics.h"
#include "figures.h"
#include <SDL2/SDL_quit.h>
#include <stdbool.h>

int run_draw_loop(graphics_t *graphics, const char *figure_path);
