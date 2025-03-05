#pragma once

typedef struct
{
    double x;
    double y;
    double z;
} vec3d_t;

typedef struct {
	double x;
	double y;
} vec2d_t;

typedef vec2d_t point2d_t;
typedef vec3d_t point3d_t;
typedef vec3d_t rotation3d_t;

vec2d_t create_vec2d(double x, double y);

vec3d_t create_vec3d(double x, double y, double z);

void point_move(vec3d_t &first, const vec3d_t &second);

void point_rotate(point3d_t &point, const point3d_t &center, const rotation3d_t &rotation);

void point_scale(point3d_t &point, const point3d_t &center, double scale);
