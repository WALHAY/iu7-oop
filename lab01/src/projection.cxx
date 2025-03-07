#include "projection.hpp"

point2d_t convert_to_screen(const point_t &point)
{
	return create_vec2d(point.x, point.y);
}
