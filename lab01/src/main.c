#include "../inc/defines.h"
#include "../inc/graphics.h"
#include "../inc/sdltools.h"
#include <stdbool.h>
#include <stdio.h>

void handle_events() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_MOUSEBUTTONDOWN &&
        event.button.button == SDL_BUTTON_LEFT) {
    }
  }
}

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
    scale_figure(figure, 200.0f);

  if (!rc)
    rc = draw_loop(renderer, figure);

  destroy_sdl(window, renderer);

  return rc;
}
