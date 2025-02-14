#include "../inc/defines.h"
#include "../inc/graphics.h"
#include "../inc/sdltools.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int rc = init_sdl();

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;

  if (!rc)
    rc = create_window_and_renderer(&window, &renderer);

  FILE *file = NULL;
  if (!rc && argc == 2) {
    file = fopen(argv[1], "r");
    if (!file)
      rc = IO_ERR;
  }

  figure_t *figure = NULL;
  if (!rc)
    rc = load_figure(file, &figure);

  if (!rc)
    scale_figure(figure, FIGURE_SCALE);

  if (!rc)
    rc = draw_loop(renderer, figure);

  destroy_sdl(window, renderer);

  if (file)
    fclose(file);

  return rc;
}
