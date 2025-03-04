#include "projection.hpp"

point2d_t convert_to_screen(const point3d_t &point)
{
	return create_vec2d(point.x * 200, point.y * 200);
}
