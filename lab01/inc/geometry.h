#pragma once

#include "defines.h"
#include <math.h>
#include <stdlib.h>

typedef struct
{
    double x;
    double y;
    double z;
} vec3d_t;

typedef vec3d_t point3d_t;

point3d_t create_point(double x, double y, double z);

point3d_t point_translate(const point3d_t *first, const point3d_t *second);

point3d_t rotate_x(const point3d_t *point, double degree);

point3d_t rotate_y(const point3d_t *point, double degree);

point3d_t scale_point(const point3d_t *point, double scale);

point3d_t projection(const point3d_t *point, double distance);
