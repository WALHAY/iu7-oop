#include "application.hpp"
#include "SDL2/SDL_keycode.h"
#include "figure.hpp"
#include "graphics.hpp"
#include "point.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_quit.h>

static void event_move(point3d_t &event, double x, double y, double z)
{
    event.x = x;
    event.y = y;
    event.z = z;
}

static void event_rotate(rotation3d_t &event, double x, double y, double z)
{
    event.x = x;
    event.y = y;
    event.z = z;
}

int populate_event(const graphics_t &graphics, event_t &event)
{
    bool *keys = (bool *)malloc(sizeof(bool) * 255);
    graphics_get_key_pressed(graphics, keys);
    for (size_t i = 0; i < 255; ++i)
    {
        if (keys[i])
        {
            switch (i)
            {
                case 'a':
					event.type = MOVE;
                    event_move(event.move, 1, 0, 0);
                    break;
                case 'd':
					event.type = MOVE;
                    event_move(event.move, -1, 0, 0);
                    break;
                case 'w':
					event.type = MOVE;
                    event_move(event.move, 0, -1, 0);
                    break;
                case 's':
					event.type = MOVE;
                    event_move(event.move, 0, 1, 0);
                    break;

				case 'z':
					event.type = ROTATE;
					event_rotate(event.rotation, 1, 0 ,0);
            }
        }
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
			figure_rotate(figure, create_vec3d(0,0,0), event.rotation);
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
