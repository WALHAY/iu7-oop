#include "application.hpp"

int run_app(graphics_t &graphics, const char *figure_path)
{
    int rc = SUCCESS;
    bool running = true;

    event_t init_event = populate_load_event(figure_path);
    controller_handler(graphics, init_event);

    init_event = populate_draw_event();
    controller_handler(graphics, init_event);

    while (!rc && running)
    {
		bool redraw = false;

        event_t event = populate_move_event();
        rc = controller_handler(graphics, event);
		if(!rc && event.type)
			redraw = true;

        event = populate_rotate_event();
        rc = controller_handler(graphics, event);
		if(!rc && event.type)
			redraw = true;

        event = populate_scale_event();
        rc = controller_handler(graphics, event);
		if(!rc && event.type)
			redraw = true;

        if(!rc && redraw)
        {
        	event = populate_draw_event();
        	rc = controller_handler(graphics, event);
        }

		event = populate_exit_event();
		rc = controller_handler(graphics, event);

		usleep(FPS_INTERVAL);
    }
    return rc == EXIT_CODE ? SUCCESS : rc;
}
