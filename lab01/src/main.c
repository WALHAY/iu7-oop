#include "../inc/defines.h"
#include "../inc/graphics.h"
#include "../inc/utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

void handle_event(bool *running) {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    *running = false;
    SDL_Quit();
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_LEFT)
      printf("Nigga");
  }
}

int main(void) {
  int rc = SUCCESS;
  bool running = true;
  rc = init_sdl();

  SDL_Surface *surface = NULL;
  SDL_Window *window = NULL;

  if (!rc)
    rc = create_window_and_surface(&window, &surface);

  if (!rc)
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 255, 0));

  figure_t *figure = NULL;
  if (!rc)
    rc = create_cube(&figure);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_UpdateWindowSurface(window);
  while (running && !rc) {
    handle_event(&running);
    // clear viewport
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 255, 255);

    SDL_RenderPresent(renderer);

    SDL_Delay(FPS_INTERVAL);
  }

  return rc;
}
