#include "../inc/vec3d.h"
#include <math.h>

#define PI 3.14

vec3d_t create_vec3d(double x, double y, double z)
{
    vec3d_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

vec3d_t point_transpose(const point3d_t *first, const point3d_t *second)
{
    double x = first->x + second->x;
    double y = first->y + second->y;
    double z = first->z + second->z;
    return create_vec3d(x, y, z);
}

vec3d_t point_rotate(const point3d_t *point, const point3d_t *center, const rotation3d_t *rotation)
{

    double x_rad = rotation->x * PI / 180;
    double y_rad = rotation->y * PI / 180;
    double z_rad = rotation->z * PI / 180;

    double x = point->x - center->x;
    double y = point->y - center->y;
    double z = point->z - center->z;

    // rotate around x
    double xcos = cos(x_rad);
    double xsin = sin(x_rad);

    y = y * xcos + z * xsin;
    z = y * -xsin + z * xcos;

    // rotate around y
    double ycos = cos(y_rad);
    double ysin = sin(y_rad);

    x = x * ycos - z * ysin;
    z = x * ysin + z * ycos;

    // rotate around z
    double zcos = cos(z_rad);
    double zsin = sin(z_rad);

    x = x * zcos + y * zsin;
    y = -x * ysin + y * zcos;

    return create_vec3d(x + center->x, y + center->y, z + center->z);
}
