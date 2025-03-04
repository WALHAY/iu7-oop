#pragma once

typedef struct
{
    double x;
    double y;
    double z;
} vec3d_t;

typedef vec3d_t point3d_t;

typedef vec3d_t rotation3d_t;

vec3d_t create_vec3d(double x, double y, double z);

vec3d_t point_transpose(const vec3d_t *first, const vec3d_t *second);

vec3d_t point_rotate(const point3d_t *point, const point3d_t *center, const rotation3d_t *rotation);

