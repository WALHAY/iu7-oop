#include "application.hpp"
#include "events.hpp"

int run_app(graphics_t &graphics, const char *figure_path)
{
    int rc = SUCCESS;
    bool running = true;

    event_t event;
    if (!rc && populate_load_event(event, figure_path))
        rc = controller_handler(graphics, event);

    if (!rc && populate_draw_event(event))
        rc = controller_handler(graphics, event);

    while (!rc && running)
    {
        bool redraw = false;

        if (!rc && populate_move_event(event))
        {
            rc = controller_handler(graphics, event);
            redraw = true;
        }

        if (!rc && populate_rotate_event(event))
        {
            rc = controller_handler(graphics, event);
            redraw = true;
        }

        if (!rc && populate_scale_event(event))
        {
            rc = controller_handler(graphics, event);
            redraw = true;
        }

        if (!rc && redraw && populate_draw_event(event))
            rc = controller_handler(graphics, event);

        if (!rc && populate_exit_event(event))
            rc = controller_handler(graphics, event);

        usleep(FPS_INTERVAL);
    }
    return rc == EXIT_CODE ? SUCCESS : rc;
}
