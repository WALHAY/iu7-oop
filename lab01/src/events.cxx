#include "events.hpp"

static int get_axis_value(const char positive, const char negative)
{
    bool positive_pressed = graphics_key_pressed(positive);
    bool negative_pressed = graphics_key_pressed(negative);
    return positive_pressed ^ negative_pressed ? (positive_pressed ? 1 : -1) : 0;
}

event_t populate_load_event(const char *path)
{
    event_t event;
    event.type = LOAD;
    event.path = path;
    return event;
}

event_t populate_exit_event()
{
	event_t event;
	event.type = NONE;
	if(graphics_exit_requested())
		event.type = EXIT;
	return event;
}

event_t populate_draw_event()
{
    event_t event;
    event.type = DRAW;
    return event;
}

event_t populate_move_event()
{
    event_t event;
    event.type = NONE;

    int move_x = get_axis_value('d', 'a');
    int move_y = get_axis_value('s', 'w');
    int move_z = get_axis_value('e', 'q');
    if (move_x || move_y || move_z)
    {
        event.type = MOVE;

        event.move = create_vec3d(move_x * MOVE_MODIFIER, move_y * MOVE_MODIFIER, move_z * MOVE_MODIFIER);
    }
    return event;
}

event_t populate_scale_event()
{
    event_t event;
	event.type = NONE;
	int scale = get_axis_value('z', 'x');
	if(scale)
	{
    	event.type = SCALE;

    	event.scale = 1.0f + scale / SCALE_MODIFIER;
	}
    return event;
}

event_t populate_rotate_event()
{
    event_t event;
    event.type = NONE;

    int rotation_x = get_axis_value('k', 'j');
    int rotation_y = get_axis_value('h', 'l');
    if (rotation_x || rotation_y)
    {
        event.type = ROTATE;

        event.rotation = create_vec3d(rotation_x * ROTATION_MODIFIER, rotation_y * ROTATION_MODIFIER, 0);
    }
    return event;
}

int controller_handler(graphics_t &graphics, const event_t &event)
{
	int rc = SUCCESS;
    static figure_t figure;

    switch (event.type)
    {
        case MOVE:
            figure_move(figure, event.move);
            break;
        case SCALE:
			figure_scale(figure, event.scale);
            break;
        case ROTATE:
            figure_rotate(figure, event.rotation);
            break;
        case LOAD:
            figure_load(figure, event.path);
			break;
        case DRAW:
			figure_draw(graphics, figure);
            break;
        case NONE:
            break;
        case EXIT:
			graphics_destroy(graphics);		
			rc = EXIT_CODE;
            break;
		default:
			rc = WRONG_EVENT_ERR;
			break;
    }
    return rc;
}
