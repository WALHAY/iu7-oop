#include "../inc/draw_logic.h"

int run_draw_loop(graphics_t *graphics, const char *figure_path)
{
    int rc = SUCCESS;
    bool running = true;
    while (!rc && running)
    {
        graphics_set_color(graphics, 0, 0, 0, 255);
        graphics_clear(graphics);

        graphics_set_color(graphics, 255, 255, 255, 255);
        rc = draw_figure(graphics, figure);

        graphics_show(graphics);

        graphics_delay(graphics, FPS_INTERVAL);
    }
    graphics_destroy(graphics);

    return rc;
}
