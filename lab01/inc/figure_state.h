#pragma once

#include "geometry.h"

typedef struct {
	point3d_t position;
	point3d_t rotation;
	float scale;
} figure_state_t;

figure_state_t *init_state(int *rc);
