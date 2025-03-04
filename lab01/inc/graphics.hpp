#pragma once 

#include <stdbool.h>
#include "defines.hpp"
#include "point.hpp"

typedef struct graphics_t graphics_t;

int graphics_init(graphics_t **graphics);

int graphics_draw_line(const graphics_t &graphics, const point3d_t &a, const point3d_t &b);

int graphics_set_color(const graphics_t &graphics, int r, int g, int b, int a);

int graphics_clear(const graphics_t &graphics);

int graphics_show(const graphics_t &graphics);

int graphics_delay(const graphics_t &graphics_t, int delay);

void graphics_destroy(graphics_t &graphics);
