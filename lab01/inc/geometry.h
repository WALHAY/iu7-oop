#pragma once

#include <stdlib.h>
#include <math.h>
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

int create_point3d(point3d_t **point);

int create_matrix3d(matrix3d_t **matrix);

int matrix_dot(matrix3d_t *result, const matrix3d_t *first, const matrix3d_t *second);

int matrix_transform(point3d_t *result, const matrix3d_t *matrix, const point3d_t *point);

int point_translate(point3d_t *result, const point3d_t *first, const point3d_t *second);

point2d_t projection(point3d_t *point, float fov, double width, double height);

point3d_t rotate_x(point3d_t *point, double degree);

point3d_t rotate_y(point3d_t *point, double degree);
