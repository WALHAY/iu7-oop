#pragma once

#include "graphics.hpp"
#include "figure.hpp"
#include "point.hpp"

typedef enum {
	MOVE,
	SCALE,
	ROTATE,
	EXIT,
	NONE
} event_type_t;

typedef struct {
	event_type_t type;
	union {
		vec3d_t move;
		rotation3d_t rotation;
		double scale;
	};
} event_t;

int request_handler(figure_t &figure, event_t &event);

int run_app(const graphics_t &graphics, const char *figure_path);
