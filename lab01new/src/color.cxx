#include "color.hpp"
#include <cstdlib>

struct color {
	int r;
	int g;
	int b;
	int alpha;
};

color_t init_rgb(int r, int g, int b)
{
	color_t rgb = (color_t) malloc(sizeof(color));
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
	rgb->alpha = 255;
	return rgb;
}

int get_color_red(const color_t &color)
{
	return color->r;
}

int get_color_green(const color_t &color)
{
	return color->g;
}

int get_color_blue(const color_t &color)
{
	return color->b;
}

int get_color_alpha(const color_t &color)
{
	return color->alpha;
}
