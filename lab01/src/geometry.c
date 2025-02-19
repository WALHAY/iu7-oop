#include "../inc/geometry.h"
#include <SDL2/SDL_rect.h>

point3d_t point_translate(const point3d_t *first, const point3d_t *second)
{
    return (point3d_t){first->x + second->x, first->y + second->y, first->z + second->z};
}

point3d_t rotate_x(const point3d_t *point, double degree)
{
    return (point3d_t){point->x, point->y * cos(degree) + point->z * sin(degree), point->y * -sin(degree) + point->z * cos(degree)};
}

point3d_t rotate_y(const point3d_t *point, double degree)
{
    return (point3d_t){point->x * cos(degree) + point->z * -sin(degree), point->y, point->x * sin(degree) + point->z * cos(degree)};
}

point3d_t scale_point(const point3d_t *point, double scale)
{
    return (point3d_t){point->x * scale, point->y * scale, point->z * scale};
}

point3d_t projection(const point3d_t *point, double distance)
{
    double z = 1 / (distance - point->z / 2);
    return (point3d_t){point->x * z, point->y * z, point->z};
}
