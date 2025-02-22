#pragma once

#include "graphics.h"
#include "figure_state.h"
#include "figures.h"
#include <SDL2/SDL_quit.h>
#include <stdbool.h>

int run_draw_loop(graphics_t *graphics, figure_state_t *state, const figure_t *figure);
