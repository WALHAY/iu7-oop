#pragma once

#include "graphics.hpp"
#include "figure.hpp"
#include "point.hpp"

typedef enum {
	NONE,
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

int controller_handler(const graphics_t &graphics, const event_t &event);

int run_app(const graphics_t &graphics, const char *figure_path);
