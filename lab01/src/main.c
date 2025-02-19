#include "../inc/defines.h"
#include "../inc/figures.h"
#include "../inc/fileio.h"
#include "../inc/sdltools.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != ARGC)
        return ARGC_ERR;

    int rc = init_sdl();

    const char *filename = argv[1];

    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;

    if (!rc)
        rc = create_window_and_renderer(&window, &renderer);

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
        rc = draw_loop(renderer, figure, state);

    destroy_sdl(window, renderer);

    free_figure(figure);
    free_state(state);

    close_file(file);

    return rc;
}
