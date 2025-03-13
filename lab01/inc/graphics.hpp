#pragma once 

#include "defines.hpp"

typedef struct point2d_t {
	double x;
	double y;
} point2d_t;

typedef struct color_rgb_t {
	int r;
	int g;
	int b;
	int alpha;
} color_rgba_t;

typedef struct graphics_t graphics_t;

color_rgba_t create_rgba(int r, int g, int b, int alpha);

point2d_t create_point2d(double x, double y);

int graphics_init(graphics_t **graphics);

int graphics_draw_line(const graphics_t &graphics, const point2d_t &a, const point2d_t &b);

int graphics_set_color(const graphics_t &graphics, const color_rgb_t &color);

int graphics_clear(const graphics_t &graphics);

int graphics_show(const graphics_t &graphics);

bool graphics_exit_requested();

bool graphics_key_pressed(const char key);

void graphics_destroy(graphics_t &graphics);
