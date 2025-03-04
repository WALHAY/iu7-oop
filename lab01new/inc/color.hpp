#pragma once

#include "defines.hpp"

struct color;

typedef struct color* color_t;

color_t init_rgb(int r, int g, int b);

int get_color_red(const color_t &color);

int get_color_green(const color_t &color);

int get_color_blue(const color_t &color);

int get_color_alpha(const color_t &color);
