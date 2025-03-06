#include "application.hpp"
#include "figure.hpp"
#include "graphics.hpp"
#include "point.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

static int get_axis_value(const char positive, const char negative)
{
    bool positive_pressed = graphics_key_pressed(positive);
    bool negative_pressed = graphics_key_pressed(negative);
    return positive_pressed ^ negative_pressed ? (positive_pressed ? 1 : -1) : 0;
}

static event_t populate_load_event(const char *path)
{
    event_t event;
    event.type = LOAD;
    event.path = path;
	printf("Event load: %s\n", event.path);
    return event;
}

static event_t populate_draw_event()
{
    event_t event;
    event.type = DRAW;
    return event;
}

static event_t populate_move_event()
{
    event_t event;
    event.type = NONE;

    int move_x = get_axis_value('d', 'a');
    int move_y = get_axis_value('s', 'w');
    int move_z = get_axis_value('e', 'q');
    if (move_x || move_y || move_z)
    {
        event.type = MOVE;

        event.move = create_vec3d(move_x * 5, move_y * 5, move_z * 5);
    }
    return event;
}

static event_t populate_scale_event()
{
    event_t event;
    event.type = SCALE;
    event.scale = 1.0f;
    return event;
}

static event_t populate_rotate_event()
{
    event_t event;
    event.type = NONE;

    int rotation_x = get_axis_value('k', 'j');
    int rotation_y = get_axis_value('h', 'l');
    if (rotation_x || rotation_y)
    {
        event.type = ROTATE;

        event.rotation = create_vec3d(rotation_x, rotation_y, 0);
    }
    return event;
}

int controller_handler(const graphics_t &graphics, const event_t &event)
{
    static figure_t figure;

    switch (event.type)
    {
        case MOVE:
            figure_move(figure, event.move);
            break;
        case SCALE:
            break;
        case ROTATE:
            figure_rotate(figure, event.rotation);
            break;
        case LOAD:
            figure_load(figure, event.path);
			break;
        case DRAW:
            graphics_set_color(graphics, 0, 0, 0, 255);
            graphics_clear(graphics);
            graphics_set_color(graphics, 255, 255, 255, 255);
            edges_draw(graphics, figure.edges);
            graphics_show(graphics);
            break;
        case EXIT:
            break;
        case NONE:
            break;
    }
    return SUCCESS;
}

int run_app(const graphics_t &graphics, const char *figure_path)
{
    int rc = SUCCESS;
    bool running = true;
    event_t load_event = populate_load_event(figure_path);
    controller_handler(graphics, load_event);
    event_t e = populate_draw_event();
    controller_handler(graphics, e);

    while (!rc && running)
    {
        if (SDL_QuitRequested())
        {
            running = false;
            break;
        }

        event_t move_event = populate_move_event();
        event_t rotation_event = populate_rotate_event();
        event_t scale_event = populate_scale_event();

        controller_handler(graphics, move_event);
        controller_handler(graphics, rotation_event);
        controller_handler(graphics, scale_event);

        if(move_event.type != NONE || scale_event.type != NONE || rotation_event.type != NONE)
        {
        	event_t draw_event = populate_draw_event();
        	controller_handler(graphics, draw_event);
        }
    }
    return rc;
}
