#pragma once

#include "geometry.h"

typedef struct {
	point3d_t position;
	rotation3d_t rotation;
	float scale;
} figure_state_t;

figure_state_t *init_state(int *rc);

void free_state(figure_state_t *state);
