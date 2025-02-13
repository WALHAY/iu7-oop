#pragma once

#include <stdlib.h>
#include "defines.h"

#define MATRIX_SIZE 3

typedef struct {
	double x;
	double y;
} point2d_t;

typedef struct {
	double x;
	double y;
	double z;
} point3d_t;

typedef struct  {
	double values[3][3];
} matrix3d_t;

int create_matrix3d(matrix3d_t **matrix);

int matrix_dot(matrix3d_t *result, const matrix3d_t *first, const matrix3d_t *second);

int matrix_transform(point3d_t *result, const matrix3d_t *matrix, const point3d_t *point);
