#include "../inc/defines.h"
#include "../inc/graphics.h"
#include "../inc/sdltools.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
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

int main(void) {
  int rc = SUCCESS;
  bool running = true;
  rc = init_sdl();

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;

  if (!rc)
    rc = create_window_and_renderer(&window, &renderer);

  figure_t *figure = NULL;
  if (!rc)
    rc = create_cube(&figure);

  if (!rc)
    scale_figure(figure, 200.0f);

  if (!rc)
    rc = draw_loop(renderer, figure);

  destroy_sdl(window, renderer);

  return rc;
}
