#include "../inc/geometry.h"
#include <SDL2/SDL_rect.h>

vec3d_t create_vec3d(double x, double y, double z)
{
    point3d_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

point3d_t point_translate(const point3d_t *first, const point3d_t *second)
{
    return create_vec3d(first->x + second->x, first->y + second->y, first->z + second->z);
}

point3d_t rotate_x(const point3d_t *point, double angle)
{
    double rad = angle * PI / 180;
    return create_vec3d(point->x, point->y * cos(rad) + point->z * sin(rad), point->y * -sin(rad) + point->z * cos(rad));
}

point3d_t rotate_y(const point3d_t *point, double angle)
{
    double rad = angle * PI / 180;
    return create_vec3d(point->x * cos(rad) + point->z * -sin(rad), point->y, point->x * sin(rad) + point->z * cos(rad));
}

point3d_t scale_point(const point3d_t *point, double scale)
{
    return create_vec3d(point->x * scale, point->y * scale, point->z * scale);
}

point3d_t projection(const point3d_t *point, double distance)
{
    double z = 1000 / (distance - point->z / 2);
    return create_vec3d(point->x / z, point->y / z, point->z);
}
