#include "../inc/defines.h"
#include "../inc/draw_logic.h"
#include "../inc/figures.h"
#include "../inc/fileio.h"
#include "../inc/graphics.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != ARGC)
        return ARGC_ERR;

    const char *filename = argv[1];

    graphics_t *graphics = NULL;
    int rc = graphics_init(&graphics);

    FILE *file = NULL;
    if (!rc)
        file = open_file(filename, "r", &rc);

    figure_t *figure = NULL;
    if (!rc)
        rc = load_figure(file, &figure);

    figure_state_t *state = NULL;
    if (!rc)
        state = init_state(&rc);

    if (!rc)
        rc = run_draw_loop(graphics, state, figure);

    free_figure(figure);
    free_state(state);

    close_file(file);

    return rc;
}
