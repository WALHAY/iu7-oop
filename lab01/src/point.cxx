#include "point.hpp"
#include "defines.hpp"
#include <math.h>

vec2d_t create_vec2d(double x, double y)
{
    vec2d_t result;
    result.x = x;
    result.y = y;
    return result;
}

vec3d_t create_vec3d(double x, double y, double z)
{
    vec3d_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void point_move(point3d_t &first, const point3d_t &second)
{
	first.x += second.x;
	first.y += second.y;
	first.z += second.z;
}

static void point_rotate_x(point3d_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double y = point.y;
	double z = point.z;

    point.y = y * cosv + z * sinv;
    point.z = y * -sinv + z * cosv;
}

static void point_rotate_y(point3d_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double x = point.x;
	double z = point.z;

    point.x = x * cosv - z * sinv;
    point.z = x * sinv + z * cosv;
}

static void point_rotate_z(point3d_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double x = point.x;
	double y = point.y;

    point.x = x * cosv + y * sinv;
    point.y = -x * sinv + y * cosv;
}

void point_rotate(point3d_t &point, const point3d_t &center, const rotation3d_t &rotation)
{
	point3d_t zeroed = create_vec3d(point.x - center.x, point.y - center.y, point.z - center.z);

	point_rotate_x(zeroed, rotation.x);
	point_rotate_y(zeroed, rotation.y);
	point_rotate_z(zeroed, rotation.z);
    
	point.x = zeroed.x + center.x;
	point.y = zeroed.y + center.y;
	point.z = zeroed.z + center.z;
}

void point_scale(point3d_t &point, const point3d_t &center, double scale)
{
	point_move(point, center);
	point.x *= scale;
	point.y *= scale;
	point.z *= scale;
	point_move(point, create_vec3d(center.x, center.y, center.z));
}
