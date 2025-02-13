#include "../inc/geometry.h"

int create_matrix3d(matrix3d_t **matrix) {
  int rc = SUCCESS;
  matrix3d_t *new_matrix = malloc(sizeof(matrix3d_t));
  if (new_matrix) {
    *matrix = new_matrix;
  } else
    rc = MEM_ERR;

  return rc;
}

int matrix_dot(matrix3d_t *result, const matrix3d_t *first,
               const matrix3d_t *second) {
  int rc = create_matrix3d(&result);
  if (!rc) {
    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
      for (size_t j = 0; j < MATRIX_SIZE; ++j) {
        for (size_t k = 0; k < MATRIX_SIZE; ++k) {
          result->values[i][j] = first->values[i][k] * second->values[k][j];
        }
      }
    }
  }
  return rc;
}

int matrix_transform(point3d_t *result, const matrix3d_t *matrix,
                     const point3d_t *point) {
  return 1;
}
