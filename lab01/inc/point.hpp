#pragma once

#include "defines.hpp"
#include <math.h>

typedef struct point_t
{
    double x;
    double y;
    double z;
} point_t;

typedef struct rotation_t {
	double x;
	double y;
	double z;
} rotation_t;

point_t create_point(double x, double y, double z);

rotation_t create_rotation(double x, double y, double z);

void point_move(point_t &first, const point_t &second);

void point_rotate(point_t &point, const point_t &center, const rotation_t &rotation);

void point_scale(point_t &point, const point_t &center, double scale);
