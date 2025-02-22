#include "../inc/draw_logic.h"

int run_draw_loop(graphics_t *graphics, figure_state_t *state, const figure_t *figure)
{
    if (!graphics_valid(graphics))
        return NULLPTR_ERR;

    int rc = SUCCESS;
    static bool running = true;
    while (!rc && running)
    {
        if (graphics_quit_requested(&rc, graphics))
        {
            running = false;
        }

        graphics_event_handler(state, graphics);

        graphic_set_color(graphics, 0, 0, 0, 255);
        graphics_clear(graphics);

        graphic_set_color(graphics, 255, 255, 255, 255);
        rc = draw_figure(graphics, state, figure);

        graphics_show(graphics);

        graphics_delay(graphics, FPS_INTERVAL);

        if (!rc)
            rc = graphics_valid(graphics) ? SUCCESS : NULLPTR_ERR;
    }
    graphics_destroy(graphics);

    return rc;
}
