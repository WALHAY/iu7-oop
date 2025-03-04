#pragma once

#include "vec3d.h"

typedef enum {
	MOVE,
	ROTATION,
	SCALE,
	QUIT
} event_type_t;

typedef struct {
	event_type_t type;
	union {
		point3d_t move;
		rotation3d_t rotation;
		double scale;
	};
} event_t;
