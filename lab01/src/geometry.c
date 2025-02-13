#include "../inc/geometry.h"

point3d_t point_translate(const point3d_t *first, const point3d_t *second) {
  return (point3d_t){first->x + second->x, first->y + second->y,
                     first->z + second->z};
}

point3d_t rotate_x(point3d_t *point, double degree) {
  return (point3d_t){point->x, point->y * cos(degree) + point->z * sin(degree),
                     point->y * -sin(degree) + point->z * cos(degree)};
}

point3d_t rotate_y(point3d_t *point, double degree) {
  return (point3d_t){point->x * cos(degree) + point->z * -sin(degree), point->y,
                     point->x * sin(degree) + point->z * cos(degree)};
}
