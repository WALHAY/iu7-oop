#include "../inc/defines.h"
#include "../inc/graphics.h"
#include "../inc/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

void handle_event(bool *running) {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_LEFT)
        printf("Nigga");
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

  SDL_UpdateWindowSurface(window);
  while (running && !rc) {
    if (SDL_QuitRequested()) {
      running = false;
      break;
    }
    // clear viewport
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    draw_figure(renderer, figure);

    SDL_RenderPresent(renderer);

    SDL_Delay(FPS_INTERVAL);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return rc;
}
