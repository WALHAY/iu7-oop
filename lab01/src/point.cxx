#include "point.hpp"

point_t create_point(double x, double y, double z)
{
    point_t result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

rotation_t create_rotation(double x, double y, double z)
{
	rotation_t rotation;
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	return rotation;
}

void point_move(point_t &first, const point_t &second)
{
	first.x += second.x;
	first.y += second.y;
	first.z += second.z;
}

static void point_rotate_x(point_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double y = point.y;
	double z = point.z;

    point.y = y * cosv + z * sinv;
    point.z = y * -sinv + z * cosv;
}

static void point_rotate_y(point_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double x = point.x;
	double z = point.z;

    point.x = x * cosv - z * sinv;
    point.z = x * sinv + z * cosv;
}

static void point_rotate_z(point_t &point, double angle)
{
	double rad = angle * PI / 180;

    double cosv = cos(rad);
    double sinv = sin(rad);

	double x = point.x;
	double y = point.y;

    point.x = x * cosv + y * sinv;
    point.y = -x * sinv + y * cosv;
}

void point_rotate(point_t &point, const point_t &center, const rotation_t &rotation)
{
	point_t zeroed = create_point(point.x - center.x, point.y - center.y, point.z - center.z);

	point_rotate_x(zeroed, rotation.x);
	point_rotate_y(zeroed, rotation.y);
	point_rotate_z(zeroed, rotation.z);
    
	point.x = zeroed.x + center.x;
	point.y = zeroed.y + center.y;
	point.z = zeroed.z + center.z;
}

void point_scale(point_t &point, const point_t &center, double scale)
{
	point_move(point, create_point(-center.x, -center.y, -center.z));
	point.x *= scale;
	point.y *= scale;
	point.z *= scale;
	point_move(point, center);
}
