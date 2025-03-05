#include "application.hpp"
#include "figure.hpp"
#include "graphics.hpp"
#include "point.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

static int get_axis_value(const graphics_t &graphics, const char positive, const char negative)
{
	bool positive_pressed = graphics_key_pressed(graphics, positive);
	bool negative_pressed = graphics_key_pressed(graphics, negative);
	return positive_pressed ^ negative_pressed ? (positive_pressed ? 1 : -1) : 0;
}

int populate_event(const graphics_t &graphics, event_t &event)
{
	int move_x = get_axis_value(graphics, 'd', 'a');
	int move_y = get_axis_value(graphics, 's', 'w');
	int move_z = get_axis_value(graphics, 'e', 'q');

	if(move_x || move_y || move_z)
	{
		event.type = MOVE;

		event.move = create_vec3d(move_x * 5, move_y * 5, move_z * 5);
	}

	int rotation_x = get_axis_value(graphics, 'k', 'j');
	int rotation_y = get_axis_value(graphics, 'h', 'l');
	if(rotation_x || rotation_y)
	{
		event.type = ROTATE;

		event.rotation = create_vec3d(rotation_x,rotation_y,0);
	}
	return SUCCESS;
}

int request_handler(figure_t &figure, event_t &event)
{
    switch (event.type)
    {
        case MOVE:
            figure_move(figure, event.move);
            break;
        case SCALE:
        case ROTATE:
			figure_rotate(figure, event.rotation);
			break;
        case NONE:
            break;
        case EXIT:
            break;
    }
    event.type = NONE;
    return SUCCESS;
}

int run_app(const graphics_t &graphics, const char *figure_path)
{
    figure_t figure;
    int rc = figure_load(figure, figure_path);
	figure_scale(figure, 200);
	figure_move(figure, create_vec3d(SDL_SCREEN_WIDTH / 2, SDL_SCREEN_HEIGHT / 2, 200));

    bool running = true;
    while (!rc && running)
    {
        if (SDL_QuitRequested())
        {
            running = false;
            break;
        }

        graphics_set_color(graphics, 0, 0, 0, 255);
        graphics_clear(graphics);

        graphics_set_color(graphics, 255, 255, 255, 255);
        edges_draw(graphics, figure.edges);

        graphics_show(graphics);

        event_t event;
        populate_event(graphics, event);
        request_handler(figure, event);

        graphics_delay(graphics, FPS_INTERVAL);
    }
    return rc;
}
