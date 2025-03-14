#pragma once

#include "graphics.hpp"
#include "point.hpp"
#include "figure.hpp"
#include "point.hpp"

typedef enum {
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

bool populate_load_event(event_t &event, const char *path);

bool populate_exit_event(event_t &event);

bool populate_draw_event(event_t &event);

bool populate_move_event(event_t &event);

bool populate_scale_event(event_t &event);

bool populate_rotate_event(event_t &event_t);

int controller_handler(graphics_t &graphics, const event_t &event);

