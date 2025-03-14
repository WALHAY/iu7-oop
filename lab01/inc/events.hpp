#pragma once

#include "graphics.hpp"
#include "point.hpp"
#include "figure.hpp"
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

typedef struct event_t {
	event_type_t type;
	union {
		point_t move;
		rotation_t rotation;
		double scale;
		const char *path;
	};
} event_t;

event_t populate_load_event(const char *path);

event_t populate_exit_event();

event_t populate_draw_event();

event_t populate_move_event();

event_t populate_scale_event();

event_t populate_rotate_event();

int controller_handler(graphics_t &graphics, const event_t &event);

