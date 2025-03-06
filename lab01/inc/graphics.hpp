#pragma once 

#include "defines.hpp"
#include "point.hpp"

typedef struct graphics_t graphics_t;

int graphics_init(graphics_t **graphics);

int graphics_draw_line(const graphics_t &graphics, const point2d_t &a, const point2d_t &b);

int graphics_set_color(const graphics_t &graphics, int r, int g, int b, int a);

int graphics_clear(const graphics_t &graphics);

int graphics_show(const graphics_t &graphics);

bool graphics_exit_requested();

bool graphics_key_pressed(const char key);

void graphics_destroy(graphics_t &graphics);
