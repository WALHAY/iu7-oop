#pragma once

#include "defines.hpp"
#include "color.hpp"
#include "geometry.hpp"

int init_graphics();

int display();

int draw_line(const vec2d_t &first, const vec2d_t &second);

int set_color(const color_t &color);

int destroy_graphics();
