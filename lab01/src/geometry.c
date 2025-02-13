#include "../inc/geometry.h"

int create_point3d(point3d_t **point) {
  int rc = SUCCESS;
  point3d_t *new_point = calloc(1, sizeof(point3d_t));
  if (new_point)
    *point = new_point;
  else
    rc = MEM_ERR;

  return rc;
}

int create_matrix3d(matrix3d_t **matrix) {
  int rc = SUCCESS;
  matrix3d_t *new_matrix = calloc(1, sizeof(matrix3d_t));
  if (new_matrix) {
    *matrix = new_matrix;
  } else
    rc = MEM_ERR;

  return rc;
}

int point_transform(point3d_t **result, const matrix3d_t *matrix,
                    const point3d_t *point) {

  int rc = create_point3d(result);

  if (!rc) {
  }
  return rc;
}

int point_translate(point3d_t *result, const point3d_t *first,
                    const point3d_t *second) {
  return 1;
}

point2d_t projection(point3d_t *point, float fov, double width, double height) {
  return (point2d_t){width / 2 + (fov * point->x) / (fov * point->z) * 100,
                     height / 2 + (fov + point->y) / (fov + point->z) * 100};
}

point3d_t rotate_x(point3d_t *point, double degree) {
  return (point3d_t){point->x, point->y * cos(degree) + point->z * sin(degree),
                     point->y * -sin(degree) + point->z * cos(degree)};
}

point3d_t rotate_y(point3d_t *point, double degree) {
  return (point3d_t){point->x * cos(degree) + point->z * -sin(degree), point->y,
                     point->x * sin(degree) + point->z * cos(degree)};
}
