#pragma once

#include "defines.hpp"
#include "graphics.hpp"
#include "point.hpp"

typedef enum {
	NONE = 0,
	LOAD,
	DRAW,
	MOVE,
	SCALE,
	ROTATE,
	EXIT
} event_type_t;

typedef struct {
	event_type_t type;
	union {
		vec3d_t move;
		rotation3d_t rotation;
		double scale;
		const char *path;
	};
} event_t;

int controller_handler(graphics_t &graphics, const event_t &event);

int run_app(graphics_t &graphics, const char *figure_path);
