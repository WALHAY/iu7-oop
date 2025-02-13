#pragma once

#include <stdlib.h>
#include <math.h>
#include "defines.h"

typedef struct {
	double x;
	double y;
	double z;
} point3d_t;

point3d_t point_translate(const point3d_t *first, const point3d_t *second);

point3d_t rotate_x(point3d_t *point, double degree);

point3d_t rotate_y(point3d_t *point, double degree);
